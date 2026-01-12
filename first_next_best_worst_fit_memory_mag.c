#include <stdio.h>

#define MAX_MEMORY 100
#define MAX_PROCESSES 10

int memory[MAX_MEMORY]; // Simulating the memory
int processSizes[MAX_PROCESSES]; // Sizes of the processes
int numProcesses;

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates free memory
    }
}

// Function to display memory state
void displayMemory() {
    printf("Memory Allocation: ");
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] != -1) {
            printf("[%d] ", memory[i]); // Process ID
        } else {
            printf("[ ] "); // Free space
        }
    }
    printf("\n");
}

// First Fit Strategy
void firstFit() {
    for (int i = 0; i < numProcesses; i++) {
        int j;
        for (j = 0; j < MAX_MEMORY; j++) {
            if (memory[j] == -1) { // Check for free memory
                int k;
                for (k = 0; k < processSizes[i]; k++) {
                    if (j + k >= MAX_MEMORY || memory[j + k] != -1) {
                        break; // Not enough space
                    }
                }
                if (k == processSizes[i]) {
                    // Allocate memory
                    for (k = 0; k < processSizes[i]; k++) {
                        memory[j + k] = i; // Assign process ID
                    }
                    printf("First Fit: Process %d allocated starting at index %d\n", i, j);
                    break;
                }
            }
        }
    }
}

// Best Fit Strategy
void bestFit() {
    for (int i = 0; i < numProcesses; i++) {
        int bestIndex = -1;
        int bestSize = MAX_MEMORY + 1;

        for (int j = 0; j < MAX_MEMORY; j++) {
            if (memory[j] == -1) {
                int k;
                for (k = 0; k < processSizes[i]; k++) {
                    if (j + k >= MAX_MEMORY || memory[j + k] != -1) {
                        break; // Not enough space
                    }
                }
                if (k == processSizes[i]) {
                    int freeSize = 0;
                    while (j + freeSize < MAX_MEMORY && memory[j + freeSize] == -1) {
                        freeSize++;
                    }
                    if (freeSize < bestSize) {
                        bestSize = freeSize;
                        bestIndex = j;
                    }
                }
            }
        }

        if (bestIndex != -1) {
            for (int k = 0; k < processSizes[i]; k++) {
                memory[bestIndex + k] = i; // Assign process ID
            }
            printf("Best Fit: Process %d allocated starting at index %d\n", i, bestIndex);
        }
    }
}

// Next Fit Strategy
void nextFit(int *lastIndex) {
    for (int i = 0; i < numProcesses; i++) {
        int j = *lastIndex;

        for (int k = 0; k < MAX_MEMORY; k++) {
            int idx = (j + k) % MAX_MEMORY; // Wrap around
            if (memory[idx] == -1) { // Check for free memory
                int l;
                for (l = 0; l < processSizes[i]; l++) {
                    if (idx + l >= MAX_MEMORY || memory[idx + l] != -1) {
                        break; // Not enough space
                    }
                }
                if (l == processSizes[i]) {
                    // Allocate memory
                    for (l = 0; l < processSizes[i]; l++) {
                        memory[idx + l] = i; // Assign process ID
                    }
                    printf("Next Fit: Process %d allocated starting at index %d\n", i, idx);
                    *lastIndex = (idx + l) % MAX_MEMORY; // Update last index
                    break;
                }
            }
        }
    }
}

// Worst Fit Strategy
void worstFit() {
    for (int i = 0; i < numProcesses; i++) {
        int worstIndex = -1;
        int worstSize = -1;

        for (int j = 0; j < MAX_MEMORY; j++) {
            if (memory[j] == -1) {
                int k;
                for (k = 0; k < processSizes[i]; k++) {
                    if (j + k >= MAX_MEMORY || memory[j + k] != -1) {
                        break; // Not enough space
                    }
                }
                if (k == processSizes[i]) {
                    int freeSize = 0;
                    while (j + freeSize < MAX_MEMORY && memory[j + freeSize] == -1) {
                        freeSize++;
                    }
                    if (freeSize > worstSize) {
                        worstSize = freeSize;
                        worstIndex = j;
                    }
                }
            }
        }

        if (worstIndex != -1) {
            for (int k = 0; k < processSizes[i]; k++) {
                memory[worstIndex + k] = i; // Assign process ID
            }
            printf("Worst Fit: Process %d allocated starting at index %d\n", i, worstIndex);
        }
    }
}

int main() {
    int lastIndex = 0;

    // Initialize memory
    initializeMemory();

    // Input process sizes
    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &numProcesses);
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d size: ", i);
        scanf("%d", &processSizes[i]);
    }

    // Perform allocations
    printf("\n--- First Fit ---\n");
    firstFit();
    displayMemory();

    // Reset memory for next allocation
    initializeMemory();

    printf("\n--- Best Fit ---\n");
    bestFit();
    displayMemory();

    // Reset memory for next allocation
    initializeMemory();

    printf("\n--- Next Fit ---\n");
    nextFit(&lastIndex);
    displayMemory();

    // Reset memory for next allocation
    initializeMemory();

    printf("\n--- Worst Fit ---\n");
    worstFit();
    displayMemory();

    return 0;
}
