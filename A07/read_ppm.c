/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/21/2025
 * Description: Read PPm file and transfer to pixels pormat.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char magic[3];
    if (fscanf(file, "%2s", magic) != 1 || strcmp(magic, "P6") != 0) {
        fprintf(stderr, "Invalid PPM file format\n");
        fclose(file);
        return NULL;
    }

  // Skip newline after magic number
    while (fgetc(file) != '\n'); 

    // Skip comment line
    if (fgetc(file) == '#') {
        while (fgetc(file) != '\n');
    } else {
        fseek(file, -1, SEEK_CUR);
    }

    if (fscanf(file, "%d %d", w, h) != 2) {
        fprintf(stderr, "Invalid image dimensions\n");
        fclose(file);
        return NULL;
    }

    int maxval;
    if (fscanf(file, "%d", &maxval) != 1 || maxval > 255) {
        fprintf(stderr, "Unsupported max color value\n");
        fclose(file);
        return NULL;
    }

  // Skip whitespace before pixel data
    while (fgetc(file) != '\n'); 

    size_t image_size = (*w) * (*h);
    struct ppm_pixel *data = (struct ppm_pixel *)malloc(image_size * sizeof(struct ppm_pixel));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    if (fread(data, sizeof(struct ppm_pixel), image_size, file) != image_size) {
        fprintf(stderr, "Error reading pixel data\n");
        free(data);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return data;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
