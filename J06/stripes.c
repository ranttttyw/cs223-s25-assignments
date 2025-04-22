/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/22/2025
 * Description: generate image with random color for each stripe
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data
{
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel *image;
};

void *start(void *userdata)
{
  struct thread_data *data = (struct thread_data *)userdata;
  // todo: your code here
  for (int i = data->starti; i < data->endi; i++)
  {
    for (int j = 0; j < data->width; j++)
    {
      data->image[i * data->width + j] = data->color;
    }
  }
  printf("Thread is coloring rows %d to %d with color: %d, %d, %d\n",
         data->starti, data->endi, data->color.red, data->color.green,
         data->color.blue);
  return NULL;
}

int main(int argc, char **argv)
{

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  // Random the color
  int size = 1024;
  int stripe_height = size / N;
  srand(time(NULL));
  struct ppm_pixel *image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel *colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t *threads = malloc(sizeof(pthread_t) * N);
  struct thread_data *data = malloc(sizeof(struct thread_data) * N);

  for (int i = 0; i < N; i++)
  {
    data[i].starti = i * stripe_height;
    data[i].endi = (i == N - 1) ? size : (i + 1) * stripe_height;
    data[i].width = size;
    data[i].height = size;
    data[i].image = image;

    data[i].color.red = rand() % 256;
    data[i].color.green = rand() % 256;
    data[i].color.blue = rand() % 256;

    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++)
  {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);

  // free memory
  free(image);
  free(colors);
  free(threads);
  free(data);
  return 0;
}
