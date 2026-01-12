#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Mutexes for each fork

// Function to simulate the eating process
void* philosopher(void* num) {
    int id = *(int*)num;
    
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2); // Simulate thinking time
        
        // Pick up left fork
        pthread_mutex_lock(&forks[id]);
        printf("Philosopher %d picked up left fork.\n", id);
        
        // Pick up right fork
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork.\n", id);
        
        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2); // Simulate eating time
        // Put down right fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", id);
        // Put down left fork
        pthread_mutex_unlock(&forks[id]);
        printf("Philosopher %d put down left fork.\n", id);
    }
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIds[NUM_PHILOSOPHERS];
    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopherIds[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopherIds[i]);
    }
    // Join threads (in a real program you might not do this)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}

