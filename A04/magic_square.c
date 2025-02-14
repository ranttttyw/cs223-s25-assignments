/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/14/2025
 * Description: Test whether a given matrix is a magic square
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

// Function to check if the matrix is a magic square
int is_magic_square(int **matrix, int n, int magic_constant) {
    int sum, i, j;

    // Check row sums
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) return 0;
    }

    // Check column sums
    for (j = 0; j < n; j++) {
        sum = 0;
        for (i = 0; i < n; i++) {
            sum += matrix[i][j];
        }
        if (sum != magic_constant) return 0;
    }

    // Check main diagonal
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += matrix[i][i];
    }
    if (sum != magic_constant) return 0;

    // Check secondary diagonal
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += matrix[i][n - i - 1];
    }
    if (sum != magic_constant) return 0;

    return 1;
}

int main() {
    int n, i, j;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading matrix size.\n");
        return 1;
    }

    // Allocate memory for the matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Read the matrix values
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error reading matrix values.\n");
                return 1;
            }
        }
    }

    // Print the matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Compute the magic constant using the first row
    int magic_constant = 0;
    for (j = 0; j < n; j++) {
        magic_constant += matrix[0][j];
    }

    // Check if it's a magic square
    if (is_magic_square(matrix, n, magic_constant)) {
        printf("M is a magic square (magic constant = %d)\n", magic_constant);
    } else {
        printf("M is NOT a magic square!\n");
    }

    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
