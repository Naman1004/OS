#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t resource_access;  // Semaphore to control access to the shared resource
sem_t read_count_access;  // Semaphore to control access to read_count
int read_count = 0;  // Number of readers currently accessing the resource

void *reader(void *arg) {
    int id = *((int *)arg);

    // Entry section for reader
    sem_wait(&read_count_access);
    read_count++;
    if (read_count == 1) {
        sem_wait(&resource_access);  // First reader locks the resource
    }
    sem_post(&read_count_access);

    // Critical section for reader
    printf("Reader %d is reading\n", id);
    sleep(1);  // Simulate reading process
    printf("Reader %d has finished reading\n", id);

    // Exit section for reader
    sem_wait(&read_count_access);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource_access);  // Last reader unlocks the resource
    }
    sem_post(&read_count_access);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);

    // Entry section for writer
    sem_wait(&resource_access);

    // Critical section for writer
    printf("Writer %d is writing\n", id);
    sleep(1);  // Simulate writing process
    printf("Writer %d has finished writing\n", id);

    // Exit section for writer
    sem_post(&resource_access);

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[5];
    int ids[5];

    // Initialize semaphores
    sem_init(&resource_access, 0, 1);
    sem_init(&read_count_access, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&resource_access);
    sem_destroy(&read_count_access);

    return 0;
}
