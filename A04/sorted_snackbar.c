/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 1/14/2025
 * Description: Allows users to add snacks to the snackbar and displays 
 * in alphabetical order.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Snack {
    char name[50];
    float cost;
    int quantity;
    struct Snack *next;
} Snack;

Snack *head = NULL;

// Function to insert a snack at the beginning of the list
void insert_first(char *name, float cost, int quantity) {
    Snack *newSnack = (Snack *)malloc(sizeof(Snack));
    strcpy(newSnack->name, name);
    newSnack->cost = cost;
    newSnack->quantity = quantity;
    newSnack->next = head;
    head = newSnack;
}

// Function to insert a snack in sorted order by name
void insert_sorted(char *name, float cost, int quantity) {
    Snack *newSnack = (Snack *)malloc(sizeof(Snack));
    strcpy(newSnack->name, name);
    newSnack->cost = cost;
    newSnack->quantity = quantity;
    newSnack->next = NULL;
    
    if (head == NULL || strcmp(name, head->name) < 0) {
        newSnack->next = head;
        head = newSnack;
        return;
    }
    
    Snack *current = head;
    while (current->next != NULL && strcmp(current->next->name, name) < 0) {
        current = current->next;
    }
    
    newSnack->next = current->next;
    current->next = newSnack;
}

// Function to print the linked list
void printList() {
    printf("\nWelcome to Sorted Sally's Snack Bar.\n\n");
    int index = 0;
    Snack *current = head;
    while (current != NULL) {
        printf("%d) %-20s cost: $%.2f quantity: %d\n", index++, current->name, current->cost, current->quantity);
        current = current->next;
    }
}

// Function to clear the linked list
void clear() {
    Snack *current = head;
    while (current != NULL) {
        Snack *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

// Function to sort by cost
void sortCost() {
    if (!head || !head->next) return;
    Snack *sorted = NULL;
    Snack *current = head;
    while (current) {
        Snack *next = current->next;
        if (!sorted || current->cost < sorted->cost) {
            current->next = sorted;
            sorted = current;
        } else {
            Snack *temp = sorted;
            while (temp->next && temp->next->cost < current->cost) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

// Function to sort by quantity
void sortQuantity() {
    if (!head || !head->next) return;
    Snack *sorted = NULL;
    Snack *current = head;
    while (current) {
        Snack *next = current->next;
        if (!sorted || current->quantity < sorted->quantity) {
            current->next = sorted;
            sorted = current;
        } else {
            Snack *temp = sorted;
            while (temp->next && temp->next->quantity < current->quantity) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

// Function to sort by name
void sortName() {
    if (!head || !head->next) return;
    Snack *sorted = NULL;
    Snack *current = head;
    while (current) {
        Snack *next = current->next;
        if (!sorted || strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Snack *temp = sorted;
            while (temp->next && strcmp(temp->next->name, current->name) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

int main() {
    int numSnacks;
    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);
    
    for (int i = 0; i < numSnacks; i++) {
        char name[50];
        float cost;
        int quantity;
        
        printf("Enter a name: ");
        scanf("%s", name);
        printf("Enter a cost: ");
        scanf("%f", &cost);
        printf("Enter a quantity: ");
        scanf("%d", &quantity);
        
        insert_sorted(name, cost, quantity);
    }
    
    printList();
    
    clear();
    return 0;
}
