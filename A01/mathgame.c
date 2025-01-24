/***************************************************
 * mathgame.c
 * Author: Ranty Wang
 * Implements a math game
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
  int rounds, num1, num2, answer, correct_answers = 0;
  printf("Welcome to Math Game!\n");

  printf("How many rounds do you want to play? ");
  scanf("%d", &rounds);

  srand(time(NULL));
  // Loop through each round and ask a random question
  for (int i = 0; i < rounds; i++) {
    // Generate random numbers for the question
    num1 = rand() % 9 + 1; 
    num2 = rand() % 9 + 1; 
    printf("\n");

    // Ask the question
    printf("%d + %d = ? ", num1, num2);
    scanf("%d", &answer);

    // Check if the answer is correct
    if (answer == num1 + num2) {
      printf("Correct!\n");
        correct_answers++;
    } 
    else {
      printf("Incorrect :(\n");
    }
  }
  printf("You answered %d/%d correctly.\n", correct_answers, rounds);

  return 0;
}
