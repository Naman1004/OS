#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void* threadFunction(void* arg) {
    // Enter critical section
    sem_wait(&mutex);
    printf("Thread %ld: Entered critical section\n", (long)arg);

    // Simulate some work
    sleep(1);

    printf("Thread %ld: Leaving critical section\n", (long)arg);
    // Leave critical section
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize semaphore
    sem_init(&mutex, 0, 1);

    // Create threads
    pthread_create(&t1, NULL, threadFunction, (void*)1);
    pthread_create(&t2, NULL, threadFunction, (void*)2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy semaphore
    sem_destroy(&mutex);
    return 0;
}
