/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Reads a PPM file and converts it to ASCII art.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
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
    char ascii_chars[] = "@#%*o;:,  ";

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = pixels[i * w + j];
            int intensity = (pixel.red + pixel.green + pixel.blue) / 3;
            
            int index = (intensity * (sizeof(ascii_chars) - 2)) / 255;
            if (index >= sizeof(ascii_chars) - 1) {
                index = sizeof(ascii_chars) - 2;
            }
            
            printf("%c", ascii_chars[index]);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}
