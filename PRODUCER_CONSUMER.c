#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0;              // Index for the next item to produce
int out = 0;             // Index for the next item to consume

sem_t empty;           // Semaphore to count empty slots
sem_t full;            // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for critical section

// Producer function
void *producer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        // Produce an item
        int item = rand() % 100;    // Random item
        sem_wait(&empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the critical section
        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer %d: Produced %d at index %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;  // Update the index
        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&full);              // Signal that a new item has been produced
        sleep(1);                     // Simulate time taken to produce
    }
}

// Consumer function
void *consumer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        sem_wait(&full);            // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock the critical section
        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumer %d: Consumed %d from index %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE; // Update the index
        pthread_mutex_unlock(&mutex);  // Unlock the critical section
        sem_post(&empty);              // Signal that an item has been consumed

        sleep(1); // Simulate time taken to consume
    }
}
int main()
{
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int producerIds[NUM_PRODUCERS], consumerIds[NUM_CONSUMERS];
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);
    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producerIds[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producerIds[i]);
    }
    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumerIds[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumerIds[i]);
    }
    // Join threads (in a real program you might not do this)
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }
    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
