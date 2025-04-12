#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

typedef struct
{
  int tid;
  int num_threads;
  int threshold;
  int blursize;
  int width;
  int height;
  struct ppm_pixel *original;
  struct ppm_pixel *bright;
  struct ppm_pixel *blurred;
} thread_args_t;

int brightness(struct ppm_pixel p)
{
  return (p.red + p.green + p.blue) / 3;
}

struct ppm_pixel clamp(struct ppm_pixel p)
{
  if (p.red > 255)
    p.red = 255;
  if (p.green > 255)
    p.green = 255;
  if (p.blue > 255)
    p.blue = 255;
  return p;
}

void *thread_work(void *arg)
{
  thread_args_t *args = (thread_args_t *)arg;

  int rows_per_thread = args->height / args->num_threads;
  int start_row = args->tid * rows_per_thread;
  int end_row = start_row + rows_per_thread;

  printf("Thread sub-image slice: rows (%d,%d)\n", start_row, end_row);

  int w = args->width;
  int h = args->height;
  int half = args->blursize / 2;

  // extract bright pixels
  for (int i = start_row; i < end_row; i++)
  {
    for (int j = 0; j < w; j++)
    {
      int idx = i * w + j;
      struct ppm_pixel p = args->original[idx];
      args->bright[idx] = (brightness(p) > args->threshold) ? p : (struct ppm_pixel){0, 0, 0};
    }
  }

  // box blur on bright image
  for (int i = start_row; i < end_row; i++)
  {
    for (int j = 0; j < w; j++)
    {
      int r = 0, g = 0, b = 0, count = 0;
      for (int di = -half; di <= half; di++)
      {
        for (int dj = -half; dj <= half; dj++)
        {
          int ni = i + di;
          int nj = j + dj;
          if (ni >= 0 && ni < h && nj >= 0 && nj < w)
          {
            int nidx = ni * w + nj;
            r += args->bright[nidx].red;
            g += args->bright[nidx].green;
            b += args->bright[nidx].blue;
            count++;
          }
        }
      }
      int idx = i * w + j;
      args->blurred[idx].red = r / count;
      args->blurred[idx].green = g / count;
      args->blurred[idx].blue = b / count;
    }
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char *filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:h")) != -1)
  {
    switch (opt)
    {
    case 'N':
      N = atoi(optarg);
      break;
    case 't':
      threshold = atof(optarg);
      break;
    case 'b':
      blursize = atof(optarg);
      break;
    case 'f':
      filename = optarg;
      break;
    case '?':
      printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]);
      break;
    case 'h':
      printf("usage: ./glow_multithreaded -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n");
      exit(0);
    }
  }

  int width, height;
  struct ppm_pixel *original = read_ppm(filename, &width, &height);
  struct ppm_pixel *bright = calloc(width * height, sizeof(struct ppm_pixel));
  struct ppm_pixel *blurred = calloc(width * height, sizeof(struct ppm_pixel));
  struct ppm_pixel *output = calloc(width * height, sizeof(struct ppm_pixel));

  pthread_t *threads = malloc(N * sizeof(pthread_t));
  thread_args_t *args = malloc(N * sizeof(thread_args_t));

  for (int i = 0; i < N; i++)
  {
    args[i] = (thread_args_t){
        .tid = i,
        .num_threads = N,
        .threshold = threshold,
        .blursize = blursize,
        .width = width,
        .height = height,
        .original = original,
        .bright = bright,
        .blurred = blurred};
    pthread_create(&threads[i], NULL, thread_work, &args[i]);
  }

  for (int i = 0; i < N; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // add blurred to original
  for (int i = 0; i < width * height; i++)
  {
    struct ppm_pixel sum = {
        original[i].red + blurred[i].red / 2,
        original[i].green + blurred[i].green / 2,
        original[i].blue + blurred[i].blue / 2};
    output[i] = clamp(sum);
  }

  write_ppm("glow.ppm", output, width, height);

  free(original);
  free(bright);
  free(blurred);
  free(output);
  free(threads);
  free(args);

  return 0;
}
