#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_LINE_LEN 1024

typedef struct
{
  int thread_id;
  int num_threads;
  char *keyword;
  int num_files;
  char **files;
} ThreadArgs;

void *grep_thread(void *arg)
{
  ThreadArgs *args = (ThreadArgs *)arg;
  int id = args->thread_id;
  int count = 0;

  // Calculate work range
  int files_per_thread = args->num_files / args->num_threads;
  int remainder = args->num_files % args->num_threads;
  int start = id * files_per_thread + (id < remainder ? id : remainder);
  int end = start + files_per_thread + (id < remainder ? 1 : 0);

  printf("Thread %d searching %d files (%d to %d)\n", id, end - start, start, end - 1);

  for (int i = start; i < end; ++i)
  {
    FILE *fp = fopen(args->files[i], "r");
    if (!fp)
    {
      perror(args->files[i]);
      continue;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), fp))
    {
      if (strstr(line, args->keyword))
      {
        printf("%d) %s:%s", id, args->files[i], line);
        count++;
      }
    }

    fclose(fp);
  }

  // Return count
  int *result = malloc(sizeof(int));
  *result = count;
  pthread_exit(result);
}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    fprintf(stderr, "usage: %s <NumThreads> <Keyword> <Files>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int num_threads = atoi(argv[1]);
  if (num_threads <= 0)
  {
    fprintf(stderr, "Error: number of threads must be > 0\n");
    return EXIT_FAILURE;
  }

  char *keyword = argv[2];
  int num_files = argc - 3;
  char **files = &argv[3];

  pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
  ThreadArgs *args = malloc(sizeof(ThreadArgs) * num_threads);

  for (int i = 0; i < num_threads; ++i)
  {
    args[i].thread_id = i;
    args[i].num_threads = num_threads;
    args[i].keyword = keyword;
    args[i].num_files = num_files;
    args[i].files = files;

    pthread_create(&threads[i], NULL, grep_thread, &args[i]);
  }

  int total_matches = 0;
  for (int i = 0; i < num_threads; ++i)
  {
    void *res;
    pthread_join(threads[i], &res);
    total_matches += *(int *)res;
    free(res);
  }

  free(threads);
  free(args);

  printf("Total matches: %d\n", total_matches);
  return 0;
}
