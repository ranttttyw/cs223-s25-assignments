/***************************************************
 * Maintains a list of snacks available for purchase
 *
 * @Author: Ranty Wang
 * @Date: 1/28/2025
 */
#include <stdio.h>
#include <string.h>

typedef struct {
  char name[50];
  float cost;
  int quantity;
} Snack;

int main() {

  Snack snacks[3] = {{"Coco Puffs", 1.50, 4},
      {"Manchego cheese", 15.50, 6},
      {"Magic beans", 0.50, 0}};

  float money;
  int choice;

  printf("Welcome to Steven Struct's Snack Bar.\n");
  printf("\nHow much money do you have? ");
  scanf("%f", &money);

  for(int i = 0; i < 3; i++) {
    printf("%d) %-20s cost: $%-8.2f quantity: %d\n", i, 
      snacks[i].name, snacks[i].cost, snacks[i].quantity);
  }

  // Ask for the user's choice
    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &choice);

    // Check if the choice is valid
    if (choice < 0 || choice >= 3) {
        printf("Invalid selection!\n");
        return 1;
    }

    // Check if the snack is affordable
    if (money < snacks[choice].cost) {
        printf("You can't afford it!\n");
    }
    // Check if the snack is available
    else if (snacks[choice].quantity == 0) {
        printf("Sorry, we are out of %s\n", snacks[choice].name);
    }
    else {
        // The user can buy the snack
        money -= snacks[choice].cost;
        snacks[choice].quantity--;  // Decrease the quantity
        printf("You bought %s\n", snacks[choice].name);
        printf("You have $%.2f left\n", money);
    }

    return 0;
}
