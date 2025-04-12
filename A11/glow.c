#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

#define THRESHOLD 200
#define BOX_SIZE 25

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

int main()
{
  int width, height;
  struct ppm_pixel *original = read_ppm("earth.ppm", &width, &height);
  int size = width * height;

  struct ppm_pixel *bright = calloc(size, sizeof(struct ppm_pixel));
  struct ppm_pixel *blurred = calloc(size, sizeof(struct ppm_pixel));
  struct ppm_pixel *output = calloc(size, sizeof(struct ppm_pixel));

  // Extract bright pixels
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      int idx = i * width + j;
      struct ppm_pixel p = original[idx];
      if (brightness(p) > THRESHOLD)
      {
        bright[idx] = p;
      }
      else
      {
        bright[idx] = (struct ppm_pixel){0, 0, 0};
      }
    }
  }

  // Box blur on bright
  int half = BOX_SIZE / 2;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      int r = 0, g = 0, b = 0, count = 0;
      for (int di = -half; di <= half; di++)
      {
        for (int dj = -half; dj <= half; dj++)
        {
          int ni = i + di;
          int nj = j + dj;
          if (ni >= 0 && ni < height && nj >= 0 && nj < width)
          {
            int nidx = ni * width + nj;
            r += bright[nidx].red;
            g += bright[nidx].green;
            b += bright[nidx].blue;
            count++;
          }
        }
      }
      int idx = i * width + j;
      blurred[idx].red = r / count;
      blurred[idx].green = g / count;
      blurred[idx].blue = b / count;
    }
  }

  // Add blurred to original
  for (int i = 0; i < size; i++)
  {
    struct ppm_pixel sum = {
        original[i].red + blurred[i].red,
        original[i].green + blurred[i].green,
        original[i].blue + blurred[i].blue};
    output[i] = clamp(sum);
  }

  write_ppm("glow.ppm", output, width, height);

  free(original);
  free(bright);
  free(blurred);
  free(output);

  return 0;
}
