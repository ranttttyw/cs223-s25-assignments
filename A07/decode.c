/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 3/7/2025
 * Description: Decodes a hidden message from a PPM file using LSB steganography.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  const char *filename = argv[1];
  int width, height;

  // Read image using your read_ppm
  struct ppm_pixel *pixels = read_ppm(filename, &width, &height);
  if (pixels == NULL)
  {
    fprintf(stderr, "Error: could not read file %s\n", filename);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);

  int total_pixels = width * height;
  int max_chars = (total_pixels * 3) / 8; // 3 LSBs per pixel, 8 bits per character
  printf("Max number of characters in the image: %d\n", max_chars);

  unsigned char current_char = 0; // To store the current character being built
  int bit_position = 0;           // To track bit assembly (we need 8 bits per character)

  // Process each pixel to extract LSBs
  for (int i = 0; i < total_pixels; i++)
  {
    struct ppm_pixel pixel = pixels[i];

    // Extract LSB from each color channel (R, G, B)
    unsigned char bits[3];
    bits[0] = pixel.red & 1;
    bits[1] = pixel.green & 1;
    bits[2] = pixel.blue & 1;

    for (int j = 0; j < 3; j++)
    {
      // Add the bit to the current character
      current_char = (current_char << 1) | bits[j];
      bit_position++;

      // Once we have 8 bits, print the character
      if (bit_position == 8)
      {
        if (current_char == '\0')
        {
          printf("\n");
          free(pixels); // Free memory when done
          return 0;
        }

        printf("%c", current_char);

        // Reset for next character
        current_char = 0;
        bit_position = 0;
      }
    }
  }

  // Clean up
  free(pixels);
  return 0;
}