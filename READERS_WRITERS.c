#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define READERS 3

sem_t mutex; // protects read_count
sem_t wrt;   // allows writer to have exclusive access
int read_count = 0;

void *reader(void *arg) {
  int id = *(int *)arg;
  while (1) {
    sem_wait(&mutex); // lock read_count
    read_count++;
    if (read_count == 1)
      sem_wait(&wrt); // first reader locks writers
		      // :contentReference[oaicite:16]{index=16}
    sem_post(&mutex);

    // reading
    printf("Reader %d is reading\n", id);
    usleep(100000);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
      sem_post(&wrt); // last reader releases writers
		      // :contentReference[oaicite:17]{index=17}
    sem_post(&mutex);
    usleep(100000);
  }
  return NULL;
}

void *writer(void *arg) {
  int id = *(int *)arg;
  while (1) {
    sem_wait(&wrt); // lock out readers and other writers
    printf("Writer %d is writing\n", id);
    usleep(200000);
    sem_post(&wrt); // release
    usleep(200000);
  }
  return NULL;
}

int main() {
  pthread_t r[READERS], w;
  int rid[READERS] = {1, 2, 3}, wid = 1;

  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);

  for (int i = 0; i < READERS; i++)
    pthread_create(&r[i], NULL, reader, &rid[i]);
  pthread_create(&w, NULL, writer, &wid);

  for (int i = 0; i < READERS; i++)
    pthread_join(r[i], NULL);
  pthread_join(w, NULL);

  sem_destroy(&mutex);
  sem_destroy(&wrt);
  return 0;
}
