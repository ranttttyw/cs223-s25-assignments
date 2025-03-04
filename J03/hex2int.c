#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char* argv[]) {
  if ( argc != 2){
    printf("Usage: ./hex2int\n");
    return 0;
  }

  //if binary
  if( argv[1][1] == 'b' && argv[1][0] == '0'){
    int sum = 0;
    //if 1, shift and add, else do nothing
    for( int i = strlen(argv[1]) - 3; i >= 0; i--){
      if( argv[1][strlen(argv[1])-i-1] == '1'){
        sum += 1 << i;
        
      }
    }
    printf("%d\n", sum
    
    );
  }

  //if hexadecimal
  if( argv[1][1] == 'x' && argv[1][0] == '0'){
    int sum = 0;

    //converting each digit from hexadecimal to decimal
    for( int i = strlen(argv[1]) - 3; i >= 0; i--){
      if( argv[1][strlen(argv[1])-i-1] != '0'){
        //seperating 0-9 from A-F
        if ( isdigit(argv[1][strlen(argv[1])-i-1])){
          //binary shifting
          sum += (argv[1][strlen(argv[1])-i-1]-'0') << (i*4);
        } else {
          sum += (argv[1][strlen(argv[1])-i-1]-55) << (i*4);
        }  
      }
    }
    printf("%d\n", sum);
  }
  return 0;
}
