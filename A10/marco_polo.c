/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/4/2025
 * Description: Uses signals to coordinate between two processes.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pid_t child_pid = 0;
pid_t parent_pid = 0;

// Parent's signal handler for SIGALRM
void parent_handler(int signum)
{
  printf("Polo [%d]\n", getpid());
  fflush(stdout);
}

// Child's signal handler for SIGALRM
void child_handler(int signum)
{
  printf("Marco [%d]\n", getpid());
  fflush(stdout);

  // Send SIGALRM back to parent
  kill(parent_pid, SIGALRM);
}

int main()
{
  parent_pid = getpid();
  printf("Parent is %d\n", parent_pid);
  fflush(stdout);

  child_pid = fork();

  if (child_pid < 0)
  {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }

  if (child_pid == 0)
  {
    signal(SIGALRM, child_handler);
    while (1)
    {
      pause();
    }
  }
  else
  {
    signal(SIGALRM, parent_handler);
    char input;
    while (1)
    {
      input = getchar();

      if (input == 'm')
      {
        kill(child_pid, SIGALRM);
      }
      else if (input == 'q')
      {
        kill(child_pid, SIGTERM);
        break;
      }
    }
  }
  return 0;
}
