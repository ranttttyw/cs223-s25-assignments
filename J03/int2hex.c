#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
  if ( argc != 2){
    printf("Usage: ./int2hex\n");
    return 0;
  }
  unsigned int integer = atoi(argv[1]);

  //printing hexadecimal
  printf("0x");
  for( int i = 7; i >= 0; i--){
    if ( (i+1) % 2 == 0){
      printf(" ");
    }
    if(((integer >> (i * 4)) & 15) > 0){
      printf("%X", ((integer >> (i * 4)) & 15));
    } else {
      printf("0");
    }
  }
  printf("\n");

  //printing binary
  printf("0b");
  for(int i = 31; i >= 0; i--){

    if ( (i+1) % 4 == 0){
      printf(" ");
    }

    if ((integer & (1 << i)) > 0){
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
  
  return 0;
}