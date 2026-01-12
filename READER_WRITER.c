#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t resourceAccess;   // Controls access to the shared resource
sem_t readCountAccess;  // Controls access to readCount
int readCount = 0;      // Number of active readers
int sharedResource = 0; // Shared resource

// Reader function
void *reader(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        // Indicate that a reader wants to read
        sem_wait(&readCountAccess);
        readCount++;
        if (readCount == 1)
        {
            // First reader locks the resource
            sem_wait(&resourceAccess);
        }
        sem_post(&readCountAccess);

        // Reading
        printf("Reader %d: Read value %d\n", id, sharedResource);
        sleep(1); // Simulate reading time

        // Indicate that a reader is done reading
        sem_wait(&readCountAccess);
        readCount--;
        if (readCount == 0)
        {
            // Last reader unlocks the resource
            sem_post(&resourceAccess);
        }
        sem_post(&readCountAccess);

        sleep(1); // Simulate idle time before next read
    }
}

// Writer function
void *writer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        // Writing (only one writer at a time)
        sem_wait(&resourceAccess);

        // Writing to the shared resource
        sharedResource++;
        printf("Writer %d: Wrote value %d\n", id, sharedResource);
        sleep(2); // Simulate writing time

        // Done writing
        sem_post(&resourceAccess);

        sleep(1); // Simulate idle time before next write
    }
}

int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&resourceAccess, 0, 1);
    sem_init(&readCountAccess, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Join threads (if needed, otherwise the program will keep running)
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&resourceAccess);
    sem_destroy(&readCountAccess);

    return 0;
}
