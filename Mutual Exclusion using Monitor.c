#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

// Define a monitor structure
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int condition;
} monitor_t;

monitor_t monitor;

void initialize_monitor(monitor_t *m) {
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cond, NULL);
    m->condition = 0;
}

void enter_monitor(monitor_t *m) {
    pthread_mutex_lock(&m->mutex);
}

void leave_monitor(monitor_t *m) {
    pthread_mutex_unlock(&m->mutex);
}

void wait_condition(monitor_t *m) {
    while (m->condition == 0) {
        pthread_cond_wait(&m->cond, &m->mutex);
    }
    m->condition = 0;
}

void signal_condition(monitor_t *m) {
    m->condition = 1;
    pthread_cond_signal(&m->cond);
}

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    free(arg);

    enter_monitor(&monitor);
    printf("Thread %d entered critical section.\n", thread_id);
    
    // Critical section
    sleep(1);  // Simulate work
    
    printf("Thread %d leaving critical section.\n", thread_id);
    leave_monitor(&monitor);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    initialize_monitor(&monitor);

    for (int i = 0; i < NUM_THREADS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&threads[i], NULL, thread_function, thread_id);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.cond);

    return 0;
}
