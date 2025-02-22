/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Reads a PPM file and applies a glitch effect.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ppm file>\n", argv[0]);
        return 1;
    }

    int w, h;
    struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read the PPM file.\n");
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", argv[1], w, h);

    // Apply randomly bit-shift color glitch
    srand(time(NULL));
    for (int i = 0; i < w * h; i++) {
        int shift = rand() % 2; // Shift by 0 or 1 bits randomly
        pixels[i].red   = (pixels[i].red << shift) & 0xFF;
        pixels[i].green = (pixels[i].green << shift) & 0xFF;
        pixels[i].blue  = (pixels[i].blue << shift) & 0xFF;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), 
      "%s-glitch.ppm", strtok(argv[1], "."));
    
    printf("Writing file %s\n", output_filename);
    write_ppm(output_filename, pixels, w, h);

    free(pixels);
    return 0;
}
