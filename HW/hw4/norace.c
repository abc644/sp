//使用chatGPT生成

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
#define LOOPS 100000
int balance = 0;

void *deposit()
{
  for (int i = 0; i < LOOPS; i++) {
    pthread_mutex_lock(&mutex1);
    balance = balance + 1;
    pthread_mutex_unlock(&mutex1);
  }
  return NULL;
}

void *withdraw()
{
  for (int i = 0; i < LOOPS; i++) {
    pthread_mutex_lock(&mutex1);
    balance = balance - 1;
    pthread_mutex_unlock(&mutex1);
  }
  return NULL;
}

int main()
{
  pthread_t thread1, thread2;

  balance = 1000; // Initial balance
  printf("Initial balance: %d\n", balance);

  pthread_create(&thread1, NULL, deposit, NULL);
  pthread_create(&thread2, NULL, withdraw, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Final balance: %d\n", balance);

  return 0;
}
