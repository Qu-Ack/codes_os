#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 5
int buffer[BUF_SIZE], in = 0, out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < 10; i++) {
    sem_wait(
	&empty); // wait for empty slot :contentReference[oaicite:7]{index=7}
    sem_wait(&mutex); // lock buffer
    buffer[in] = i;
    printf("Producer %d produced %d at %d\n", id, i, in);
    in = (in + 1) % BUF_SIZE;
    sem_post(&mutex); // unlock buffer
    sem_post(
	&full); // signal new full slot :contentReference[oaicite:8]{index=8}
    usleep(100000);
  }
  return NULL;
}

void *consumer(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < 10; i++) {
    sem_wait(
	&full); // wait for filled slot :contentReference[oaicite:9]{index=9}
    sem_wait(&mutex); // lock buffer
    int item = buffer[out];
    printf("Consumer %d consumed %d from %d\n", id, item, out);
    out = (out + 1) % BUF_SIZE;
    sem_post(&mutex); // unlock buffer
    sem_post(&empty); // signal new empty slot
		      // :contentReference[oaicite:10]{index=10}
    usleep(150000);
  }
  return NULL;
}

int main() {
  pthread_t prod[2], cons[2];
  int ids[2] = {1, 2};

  sem_init(&empty, 0, BUF_SIZE);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);

  for (int i = 0; i < 2; i++)
    pthread_create(&prod[i], NULL, producer, &ids[i]);
  for (int i = 0; i < 2; i++)
    pthread_create(&cons[i], NULL, consumer, &ids[i]);

  for (int i = 0; i < 2; i++) {
    pthread_join(prod[i], NULL);
    pthread_join(cons[i], NULL);
  }

  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&mutex);
  return 0;
}
