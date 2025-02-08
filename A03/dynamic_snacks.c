/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/7/2025
 * Description: Adding list of snacks in snackbar.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    float cost;
    int quantity;
} Snack;

int main() {
    int num_snacks;
    printf("Enter a number of snacks: ");
    scanf("%d", &num_snacks);

    // Allocate memory for the snacks array
    Snack *snacks = (Snack *)malloc(num_snacks * sizeof(Snack));
    if (snacks == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Get user input for each snack
    for (int i = 0; i < num_snacks; i++) {
        printf("Enter a name: ");
        scanf("%s", snacks[i].name);
        printf("Enter a cost: ");
        scanf("%f", &snacks[i].cost);
        printf("Enter a quantity: ");
        scanf("%d", &snacks[i].quantity);
    }

    // Print the snacks list
    printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");
    for (int i = 0; i < num_snacks; i++) {
        printf("%d) %-20s cost: $%.2f     quantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
    }

    free(snacks);

    return 0;
}
