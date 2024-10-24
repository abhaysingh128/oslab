#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer size

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;  // Track positions in buffer

sem_t empty;  // Count of empty slots
sem_t full;   // Count of full slots
pthread_mutex_t mutex;  // Mutex for critical section

void *producer(void *arg) {
    int item;
    while(1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Decrement empty, wait if buffer is full
        pthread_mutex_lock(&mutex);  // Lock buffer

        // Add item to buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Unlock buffer
        sem_post(&full);  // Increment full slots
        sleep(1);  // Simulate production delay
    }
}

void *consumer(void *arg) {
    int item;
    while(1) {
        sem_wait(&full);  // Decrement full, wait if buffer is empty
        pthread_mutex_lock(&mutex);  // Lock buffer

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Unlock buffer
        sem_post(&empty);  // Increment empty slots
        sleep(2);  // Simulate consumption delay
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer starts with all slots empty
    sem_init(&full, 0, 0);  // No full slots initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish (they won't in this case as loops are infinite)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}
