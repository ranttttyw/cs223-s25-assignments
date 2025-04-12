/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Writes a PPM image file in binary format.
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char *filename, struct ppm_pixel *pixels, int w, int h)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }

    if (pixels == NULL)
    {
        fprintf(stderr, "write_ppm: pixel data is NULL!\n");
        fclose(file);
        return;
    }

    if (w <= 0 || h <= 0)
    {
        // fprintf(stderr, "write_ppm: invalid width/height (%d x %d)\n", w, h);
        fclose(file);
        return;
    }

    fprintf(file, "P6\n%d %d\n255\n", w, h);
    size_t written = fwrite(pixels, sizeof(struct ppm_pixel), w * h, file);
    // printf("write_ppm: wrote %zu of %d pixels\n", written, w * h);
    fclose(file);
    // printf("write_ppm: Finished writing %s\n", filename);
}
