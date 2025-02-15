#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N]; // Mutexes for forks

void think(int philosopher) {
    printf("Philosopher %d is thinking\n", philosopher);
    usleep(rand() % 1000 + 500);
}

void eat(int philosopher) {
    printf("Philosopher %d is eating\n", philosopher);
    usleep(rand() % 1000 + 500);
}

void* philosopher(void* num) {
    int id = *(int*)num;
    
    while (1) {
        think(id);

        // Pick up the left fork
        pthread_mutex_lock(&forks[id]);
        printf("Philosopher %d picked up left fork\n", id);

        // Pick up the right fork
        pthread_mutex_lock(&forks[(id + 1) % N]);
        printf("Philosopher %d picked up right fork\n", id);

        eat(id);

        // Put down the right fork
        pthread_mutex_unlock(&forks[(id + 1) % N]);
        printf("Philosopher %d put down right fork\n", id);

        // Put down the left fork
        pthread_mutex_unlock(&forks[id]);
        printf("Philosopher %d put down left fork\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads (not really needed as they run infinitely)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
