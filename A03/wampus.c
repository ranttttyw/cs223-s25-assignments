/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/7/2025
 * Description: Randomly places a Wampus within 
 * a NxM grid fill in the remaining cells with 
 * their distance from the Wampus. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    int rows, cols;
    printf("Number of rows: ");
    scanf("%d", &rows);
    printf("Number of columns: ");
    scanf("%d", &cols);

    // Allocate memory for the grid
    char **grid = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (char *)malloc(cols * sizeof(char));
    }

    // Seed random number generator
    srand(time(NULL));
    int wampus_x = rand() % rows;
    int wampus_y = rand() % cols;

    // Fill the grid with Manhattan distances
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == wampus_x && j == wampus_y) {
                grid[i][j] = 'W';
            } else {
                grid[i][j] = '0' + manhattan_distance(i, j, wampus_x, wampus_y);
            }
        }
    }

    // Print the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
