#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char word[31];
  printf("%s", "Enter a string: ");
  scanf("%s", word);
  int wordLength = strlen(word);
  char* arr = malloc(sizeof(char) * wordLength * wordLength);
  for (int i = 0; i < wordLength; i++) {
    for (int j = 0; j < wordLength; j++) {
      if (i == 0 | i == wordLength - 1) {
        arr[i * wordLength + j] = word[j];
      }
      else if (j == i) {
        arr[i * wordLength + j] = word[i];
      }
      else {
        arr[i * wordLength + j] = ' ';
      }
    }
  }
  for (int i = 0; i < wordLength; i++) {
    for (int j = 0; j < wordLength; j++) {
      printf("%c ", arr[i * wordLength + j]);
    }
    printf("\n");
  }
  free(arr);
  return 0;
}
