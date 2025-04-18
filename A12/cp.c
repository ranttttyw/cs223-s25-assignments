#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

int buffer[N];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int produce_item()
{
  return rand() % 10;
}

void consume_item(int item)
{
  printf("Received item: %d\n", item);
}

void *producer(void *arg)
{
  while (1)
  {
    int item = produce_item();
    sleep(1);
    pthread_mutex_lock(&mutex);
    while (count == N)
    {
      pthread_cond_wait(&empty, &mutex); // wait for space
    }

    buffer[in] = item;
    in = (in + 1) % N;
    count++;

    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg)
{
  while (1)
  {
    pthread_mutex_lock(&mutex);
    while (count == 0)
    {
      pthread_cond_wait(&full, &mutex); // wait for item
    }

    int item = buffer[out];
    out = (out + 1) % N;
    count--;

    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);

    consume_item(item);
  }
  return NULL;
}

int main()
{
  srand(time(NULL));

  pthread_t prod, cons;
  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  return 0;
}
