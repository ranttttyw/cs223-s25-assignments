#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

struct account
{
  float balance;
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

struct thread_data
{
  struct account *fromAccount;
  struct account *toAccount;
  float amount;
};

void *Transfer(void *args)
{
  struct thread_data *data = (struct thread_data *)args;
  struct account *fromAcct = data->fromAccount;
  struct account *toAcct = data->toAccount;
  float amt = data->amount;

  for (int i = 0; i < 1000; i++)
  {
    if (fromAcct < toAcct)
    {
      pthread_mutex_lock(&fromAcct->lock);
      pthread_mutex_lock(&toAcct->lock);
    }
    else
    {
      pthread_mutex_lock(&toAcct->lock);
      pthread_mutex_lock(&fromAcct->lock);
    }

    // wait for sufficient funds
    while (fromAcct->balance < amt)
    {
      pthread_cond_wait(&fromAcct->cond, &fromAcct->lock);
    }

    fromAcct->balance -= amt;
    assert(fromAcct->balance >= 0);

    toAcct->balance += amt;

    // signal others waiting on either account
    pthread_cond_signal(&fromAcct->cond);
    pthread_cond_signal(&toAcct->cond);

    pthread_mutex_unlock(&fromAcct->lock);
    pthread_mutex_unlock(&toAcct->lock);

    for (volatile int j = 0; j < 10000; j++)
      ;
  }

  return NULL;
}

int main()
{
  struct account A, B;
  A.balance = 5000;
  B.balance = 5000;
  pthread_mutex_init(&(A.lock), NULL);
  pthread_mutex_init(&(B.lock), NULL);

  pthread_cond_init(&(A.cond), NULL);
  pthread_cond_init(&(B.cond), NULL);

  printf("Starting balance A: %.2f\n", A.balance);
  printf("Starting balance B: %.2f\n", B.balance);

  struct thread_data dataA;
  dataA.fromAccount = &B;
  dataA.toAccount = &A;
  dataA.amount = 1000;

  struct thread_data dataB;
  dataB.fromAccount = &A;
  dataB.toAccount = &B;
  dataB.amount = 1000;

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, Transfer, &dataA);
  pthread_create(&thread2, NULL, Transfer, &dataB);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Ending balance A: %.2f\n", A.balance);
  fflush(stdout); // 🆕 ADDED
  printf("Ending balance B: %.2f\n", B.balance);
  fflush(stdout); // 🆕 ADDED

  pthread_mutex_destroy(&A.lock);
  pthread_mutex_destroy(&B.lock);
  pthread_cond_destroy(&A.cond);
  pthread_cond_destroy(&B.cond);
  return 0;
}
