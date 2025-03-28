/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 3/28/2025
 * Description: Searches files for a keyword using multiple
 * processes and reports total matches.

 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAX_FILES 256
#define MAX_LINE_LEN 1024

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    fprintf(stderr, "usage: %s <NumProcesses> <Keyword> <Files>\n", argv[0]);
    return 1;
  }

  int numProcesses = atoi(argv[1]);
  char *keyword = argv[2];
  int numFiles = argc - 3;

  if (numProcesses <= 0 || numFiles <= 0)
  {
    fprintf(stderr, "Error: Invalid number of processes or files.\n");
    return 1;
  }

  char **files = &argv[3];
  printf("Searching %d files for keyword: %s\n", numFiles, keyword);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  int totalMatches = 0;
  int filesPerProcess = numFiles / numProcesses;
  int extra = numFiles % numProcesses;

  for (int i = 0; i < numProcesses; i++)
  {
    int startIdx = i * filesPerProcess + (i < extra ? i : extra);
    int count = filesPerProcess + (i < extra ? 1 : 0);
    pid_t pid = fork();

    if (pid == 0)
    {
      // Child process
      int matchCount = 0;
      printf("Process [%d] searching %d files (%d to %d)\n",
             getpid(), count, startIdx + 3, startIdx + 3 + count - 1);

      for (int j = startIdx; j < startIdx + count; j++)
      {
        FILE *f = fopen(files[j], "r");
        if (!f)
        {
          printf("Process [%d] Error: Cannot open file\n", getpid());
          continue;
        }

        char line[MAX_LINE_LEN];
        while (fgets(line, sizeof(line), f))
        {
          if (strstr(line, keyword))
          {
            matchCount++;
          }
        }
        fclose(f);
      }

      exit(matchCount > 255 ? 255 : matchCount);
    }
  }

  // Parent waits for all children
  for (int i = 0; i < numProcesses; i++)
  {
    int status;
    wait(&status);
    if (WIFEXITED(status))
    {
      totalMatches += WEXITSTATUS(status);
    }
  }

  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) +
                   (end.tv_usec - start.tv_usec) / 1000000.0;

  printf("Total occurances: %d\n", totalMatches);
  printf("Elapsed time is %f\n", elapsed);

  return 0;
}
