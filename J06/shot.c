/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/22/2025
 * Description: waiting for SIGINT signal
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_Printer(int sig)
{
  printf("Help! I've been shot!\n");
  exit(0);
}

int main()
{
  signal(SIGINT, signal_Printer);
  while (1)
  {
    pause();
  }
  return 0;
}
