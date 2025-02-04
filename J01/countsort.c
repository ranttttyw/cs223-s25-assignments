/***************************************************
 * Takes simple digits and print sorted result
 *
 * @Author: Ranty Wang and Juliette Ortiz
 * @Date: 2/4/2025
 */
#include <stdio.h>
#include <string.h>

int main() {
   char input[31];
   int len;
   char number[] = "0123456789"; 

   printf("Enter digits: ");
   scanf("%s", input);
   len = strlen(input);

   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < len; j++) {
         if (input[j] == number[i]) {
            printf("%c ", input[j]);
         }
      }
   }
   printf("\n");
   return 0;
}
