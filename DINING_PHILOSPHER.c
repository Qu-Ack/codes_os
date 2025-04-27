#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
sem_t forks[N];
sem_t room; // allows up to N-1 philosophers to try picking forks
	    // :contentReference[oaicite:12]{index=12}

void *philosopher(void *arg) {
  int id = *(int *)arg;
  int left = id, right = (id + 1) % N;
  while (1) {
    // think
    printf("Philosopher %d thinking\n", id);
    usleep(100000);

    sem_wait(&room);	     // enter room
    sem_wait(&forks[left]);  // pick up left fork
			     // :contentReference[oaicite:13]{index=13}
    sem_wait(&forks[right]); // pick up right fork

    // eat
    printf("Philosopher %d eating\n", id);
    usleep(100000);

    sem_post(&forks[left]);  // put down left fork
    sem_post(&forks[right]); // put down right fork
    sem_post(&room);	     // leave room
  }
  return NULL;
}

int main() {
  pthread_t th[N];
  int ids[N];
  sem_init(&room, 0, N - 1);
  for (int i = 0; i < N; i++)
    sem_init(&forks[i], 0, 1);

  for (int i = 0; i < N; i++) {
    ids[i] = i;
    pthread_create(&th[i], NULL, philosopher, &ids[i]);
  }
  for (int i = 0; i < N; i++)
    pthread_join(th[i], NULL);

  for (int i = 0; i < N; i++)
    sem_destroy(&forks[i]);
  sem_destroy(&room);
  return 0;
}
