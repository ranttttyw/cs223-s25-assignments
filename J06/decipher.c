/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/22/2025
 * Description: decode the message
 ---------------------------------------------*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char c = fgetc(fp);
    while (c != EOF)
    {
        // Decode by right-shifting
        char decoded = (c >> 1) & 0x7F;
        printf("%c", decoded);
        c = fgetc(fp);
    }

    fclose(fp);
    return 0;
}