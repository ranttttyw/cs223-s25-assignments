/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Reads a PPM file, writes 
 * it to a new file, then reads back the new file.
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
    int w, h;
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

    if (!pixels) {
        fprintf(stderr, "Error: Failed to read the PPM file.\n");
        return 1;
    }
    
    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    write_ppm("test.ppm", pixels, w, h);
    free(pixels);

    struct ppm_pixel* new_pixels = read_ppm("test.ppm", &w, &h);
    if (!new_pixels) {
        fprintf(stderr, "Error: Failed to read the written PPM file.\n");
        return 1;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = new_pixels[i * w + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(new_pixels);
    return 0;
}

