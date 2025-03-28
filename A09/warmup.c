/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 3/28/2025
 * Description: Creates a fixed process tree using fork()
 * to print messages from each process.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  printf("%d] A0\n", getpid());

  pid_t pid_b1 = fork();

  if (pid_b1 < 0)
  {
    perror("fork failed");
    exit(1);
  }

  if (pid_b1 == 0)
  {
    // B1 process
    printf("%d] B1\n", getpid());
    printf("%d] Bye\n", getpid());
  }
  else
  {
    // B0 process
    printf("%d] B0\n", getpid());

    pid_t pid_c1 = fork();

    if (pid_c1 < 0)
    {
      perror("fork failed");
      exit(1);
    }

    if (pid_c1 == 0)
    {
      // C1 process
      printf("%d] C1\n", getpid());
      printf("%d] Bye\n", getpid());
    }
    else
    {
      // C0 process
      printf("%d] C0\n", getpid());
      printf("%d] Bye\n", getpid());
    }
  }

  return 0;
}