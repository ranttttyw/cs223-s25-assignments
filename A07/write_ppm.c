/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Writes a PPM image file in binary format.
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!


void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "P6\n%d %d\n255\n", w, h);
    fwrite(pixels, sizeof(struct ppm_pixel), w * h, file);
    fclose(file);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
}
