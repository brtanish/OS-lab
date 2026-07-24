#include <stdio.h>      // Standard input/output functions
#include <stdlib.h>     // Standard library
#include <pthread.h>    // Thread library
#include <semaphore.h>  // Semaphore library
#include <unistd.h>     // sleep() function

#define BUFFER_SIZE 5   // Size of the shared buffer

// Shared buffer and index variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

// Producer thread function
void *producer(void *arg)
{
    int item;

    // Produce 10 items
    for (int i = 1; i <= 10; i++)
    {
        item = i;

        // Wait if buffer is full
        sem_wait(&empty);

        // Enter critical section
        sem_wait(&mutex);

        // Add item to buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);

        // Move to next buffer position
        in = (in + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);

        // Increase number of filled slots
        sem_post(&full);

        // Delay producer
        sleep(1);
    }

    pthread_exit(NULL);
}

// Consumer thread function
void *consumer(void *arg)
{
    int item;

    // Consume 10 items
    for (int i = 1; i <= 10; i++)
    {
        // Wait if buffer is empty
        sem_wait(&full);

        // Enter critical section
        sem_wait(&mutex);

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);

        // Move to next buffer position
        out = (out + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);

        // Increase number of empty slots
        sem_post(&empty);

        // Delay consumer
        sleep(2);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producerThread, consumerThread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);            // Initially no filled slots
    sem_init(&mutex, 0, 1);           // Mutex initialized to 1

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}