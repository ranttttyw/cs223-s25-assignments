/***************************************************
 * Random generate price and compare guesses
 *
 * @Author: Ranty Wang and Juliette Ortiz
 * @Date: 2/4/2025
 */

#include <stdio.h>
#include <stdlib.h>

void comparePrices(int *input, int *c1, int *c2, int *price){
      if (*price < *input && *price < *c1 && *price < *c2){
         printf("Sorry. No one wins the dishwasher\n");
      }
      else {
         int newC1 = *c1 - *price;
         int newC2 = *c2 - *price;
         int newInput = *input - *price;
         int winner;

         if (abs(newC1) < abs(newC2) && abs(newC1) < abs(newInput)
            && newC1 <= 0) {
            printf("AI contestant #1 wins the dishwasher\n");
         } else if(abs(newC2) < abs(newC1) && abs(newC2) < abs(newInput)
            && newC2 <= 0) {
               printf("AI contestant #2 wins the dishwasher\n");
         } else if(abs(newInput) < abs(newC1) && abs(newInput) < abs(newC2)
            && newInput <= 0) {
               printf("Congratulations!! You win the dishwasher!\n");
         }
      }
   }

int main() {
   int input;
   int computer1;
   int computer2;
   int price;

   printf("Welcome to the Price Right!\n");
   printf("Enter a guess to win a luxurious dishwasher: $");
   scanf("%d", &input);

   computer1 = rand() % (5000 - 3000 + 1) + 3000;
   computer2 = rand() % (5000 - 3000 + 1) + 3000;
   price = rand() % (5000 - 3000 + 1) + 3000;

   printf("AI contestant #1 guesses $%d\n", computer1);
   printf("AI contestant #2 guesses $%d\n", computer2);
   printf("The dishwasher cost $%d\n", price);
   comparePrices(&input, &computer1, &computer2, &price);

   return 0;
}

