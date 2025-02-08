/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 2/7/2025
 * Description: Repeat string for required times
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char word[32];
    int count;

    printf("Enter a word: ");
    scanf("%31s", word); // Limit input to prevent overflow
    printf("Enter a count: ");
    scanf("%d", &count);

    // Calculate the required memory size
    size_t word_len = strlen(word);
    size_t total_size = word_len * count + 1; // +1 for null terminator

    // Check for overflow and allocate memory
    if (total_size <= word_len || total_size <= count) {
        printf("Cannot allocate new string. Exiting...\n");
        return 1;
    }

    char *result = (char *)malloc(total_size);
    if (result == NULL) {
        printf("Cannot allocate new string. Exiting...\n");
        return 1;
    }

    // Build the repeated string
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(result, word);
    }

    printf("Your word is %s\n", result);
    
    free(result); // Free allocated memory
    return 0;
}
