/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/22/2025
 * Description: ask user and print a sentences
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int boolean;
    int numAdjectives;

    printf("Boolean: ");
    scanf("%d", &boolean);

    printf("Number: ");
    scanf("%d", &numAdjectives);

    // Allocate space for each adjective
    char **adjectives = malloc(numAdjectives * sizeof(char *));
    if (adjectives == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numAdjectives; i++)
    {
        adjectives[i] = malloc(33 * sizeof(char)); // 32 + '\0'
        if (adjectives[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int j = 0; j < i; j++)
            {
                free(adjectives[j]);
            }
            free(adjectives);
            return 1;
        }
        printf("Adjective: ");
        scanf("%s", adjectives[i]);
    }

    printf("You are the most ");
    for (int i = numAdjectives - 1; i >= 0; i--)
    {
        printf("%s", adjectives[i]);
        if (i == 1)
        {
            printf(", and ");
        }
        else if (i > 1)
        {
            printf(", ");
        }
    }
    printf(" person that I know and you know its %s!\n", boolean ? "true" : "false");

    // Free
    for (int i = 0; i < numAdjectives; i++)
    {
        free(adjectives[i]);
    }
    free(adjectives);

    return 0;
}
