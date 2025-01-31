/***************************************************
 * Replaces each letter with a letter that is X 
 * positions from it in the alphabet.
 *
 * @Author: Ranty Wang
 * @Date: 1/28/2025
 */
#include <stdio.h>
#include <string.h>

void cypher_word(char* word, int shift){
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') {
      word[i] = (word[i] - 'a' + shift + 26) % 26 + 'a';
    }
  }
}

int main() {
  char word[100];
  int shift;

  printf("Enter a word: ");
  scanf("%s", word);

  printf("Enter a shift: ");
  scanf("%d", &shift);

  cypher_word(word, shift);

  printf("Your cypher is %s\n", word);

  return 0;
}
