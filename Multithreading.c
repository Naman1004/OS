#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

pthread_mutex_t lock;
pthread_cond_t cond;
int counter = 0;
int waiting_threads = 0;

void *increment_counter(void *threadid) {
    long tid = (long)threadid;
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        if (i == NUM_INCREMENTS - 1) {
            waiting_threads++;
            if (waiting_threads == NUM_THREADS) {
                pthread_cond_signal(&cond);
            }
        }
        pthread_mutex_unlock(&lock);
    }
    printf("Thread %ld finished.\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Initialize the mutex and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    pthread_mutex_lock(&lock);
    while (waiting_threads < NUM_THREADS) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);

    // Wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    printf("Final counter value: %d\n", counter);
    pthread_exit(NULL);
}
