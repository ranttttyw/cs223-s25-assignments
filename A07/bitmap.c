/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 3/6/2025
 * Description: 1bpp 8x8 Bitmap Renderer
 ---------------------------------------------*/
#include <stdio.h>

int main()
{
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  // Loop through each bit position (64 bits, 8 rows of 8 bits)
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      int bitIndex = row * 8 + col;

      if (img & (0x1ul << (63 - bitIndex)))
      {
        printf("@");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }

  return 0;
}
