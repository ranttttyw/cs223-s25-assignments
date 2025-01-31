/***************************************************
 * Asks the user for a word and creates a bad password from it。
 *
 * @Author: Ranty Wang
 * @Date: 1/28/2025
 */
#include <stdio.h>
#include <string.h>

void create_bad_pass(char* word){
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == 'e') {
      word[i] = '3';
    }
    if (word[i] == 'l') {
      word[i] = '1';
    }
    if (word[i] == 'a') {
      word[i] = '@';
    }
  }
}

int main() {
  char word[100];

  //User Input
  printf("Enter a word: ");
  scanf("%s", word);
  create_bad_pass(word);

  //Print the bad password
  printf("Your bad password is %s\n", word);
  return 0;
}



