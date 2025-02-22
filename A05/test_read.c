/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Test read_ppm and print result
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
    int w, h;
        
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
    
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read the PPM file.\n");
        return 1;
    }

    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = pixels[i * w + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}