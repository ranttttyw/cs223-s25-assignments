#include <stdio.h>
#include <stdlib.h>

typedef struct BraceLocation {
    int line;
    int column;
    struct BraceLocation* next;
} BraceLocation;

BraceLocation* push(BraceLocation* top, int line, int column) {
    BraceLocation* newNode = malloc(sizeof(BraceLocation));
    if (!newNode) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    newNode->line = line;
    newNode->column = column;
    newNode->next = top;
    return newNode;
}

BraceLocation* pop(BraceLocation* top, int* line, int* column) {
    if (top == NULL) {
        return NULL;
    }
    *line = top->line;
    *column = top->column;
    BraceLocation* nextNode = top->next;
    free(top);
    return nextNode;
}

void clearStack(BraceLocation* top) {
    while (top != NULL) {
        BraceLocation* temp = top;
        top = top->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: ./match_braces\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    int line = 1, column = 0;
    int ch;
    BraceLocation* stack = NULL;

    while ((ch = fgetc(file)) != EOF) {
        column++;
        if (ch == '\n') {
            line++;
            column = 0;
        } else if (ch == '{') {
            stack = push(stack, line, column);
        } else if (ch == '}') {
            int openLine, openColumn;
            if (stack == NULL) {
                printf("Unmatched brace on Line %d and Column %d\n", line, column);
            } else {
                stack = pop(stack, &openLine, &openColumn);
                printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
                       openLine, openColumn, line, column);
            }
        }
    }

    // Check for unmatched opening braces
    while (stack != NULL) {
        printf("Unmatched brace on Line %d and Column %d\n", stack->line, stack->column);
        stack = pop(stack, &line, &column);
    }

    clearStack(stack);
    fclose(file);
    return 0;
}