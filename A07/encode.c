/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 3/6/2025
 * Description: Encodes a secret message into a PPM image using LSB steganography.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

// generate the output filename -encoded.ppm
void get_encoded_filename(const char *input, char *output)
{
  strcpy(output, input);
  char *dot = strrchr(output, '.');
  if (dot != NULL)
  {
    *dot = '\0';
  }
  strcat(output, "-encoded.ppm");
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  const char *filename = argv[1];
  int width, height;

  // Read the PPM image
  struct ppm_pixel *pixels = read_ppm(filename, &width, &height);
  if (pixels == NULL)
  {
    fprintf(stderr, "Error: could not read file %s\n", filename);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);

  // Calculate max characters we can store
  int total_pixels = width * height;
  int max_chars = (total_pixels * 3) / 8 - 1;
  printf("Max number of characters in the image: %d\n", max_chars);

  char message[1000]; // Message size limit
  printf("Enter a phrase: ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    fprintf(stderr, "Error reading message\n");
    free(pixels);
    return 1;
  }

  // Remove newline
  message[strcspn(message, "\n")] = '\0';

  int message_length = strlen(message) + 1; // +1 for null terminator
  if (message_length > max_chars)
  {
    fprintf(stderr, "Message too long to fit in image (max %d characters)\n", max_chars);
    free(pixels);
    return 1;
  }

  int bit_position = 0;
  int char_index = 0;

  for (int i = 0; i < total_pixels && char_index < message_length; i++)
  {
    struct ppm_pixel *pixel = &pixels[i];

    // Get the current character
    unsigned char current_char = message[char_index];

    // Loop over red, green, blue
    for (int j = 0; j < 3 && char_index < message_length; j++)
    {
      unsigned char *color_channel;
      if (j == 0)
        color_channel = &pixel->red;
      else if (j == 1)
        color_channel = &pixel->green;
      else
        color_channel = &pixel->blue;

      int bit = (current_char >> (7 - bit_position)) & 1;

      *color_channel = (*color_channel & ~1) | bit;

      bit_position++;
      if (bit_position == 8)
      {
        // Move to next character
        bit_position = 0;
        char_index++;
        current_char = message[char_index]; // Load next char (including null terminator)
      }
    }
  }

  // Generate output filename
  char output_filename[256];
  get_encoded_filename(filename, output_filename);

  // Write encoded image
  printf("Writing file %s\n", output_filename);
  write_ppm(output_filename, pixels, width, height);

  // Clean up
  free(pixels);

  return 0;
}
