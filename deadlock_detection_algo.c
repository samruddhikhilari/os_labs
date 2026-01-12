#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

int allocation[P][R]; // Allocation matrix
int max[P][R];        // Maximum matrix
int need[P][R];       // Need matrix
int available[R];     // Available resources

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to detect deadlock using the wait-for graph
bool isDeadlocked() {
    bool finish[P] = {false};
    int count = 0;

    while (count < P) {
        bool found = false;

        for (int p = 0; p < P; p++) {
            // Check if process p can finish
            if (!finish[p]) {
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > available[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    // Simulate finishing process p
                    for (int j = 0; j < R; j++) {
                        available[j] += allocation[p][j]; // Release allocated resources
                    }
                    finish[p] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found) {
            // If no process could finish, we have a deadlock
            printf("Deadlock detected among the following processes:\n");
            for (int i = 0; i < P; i++) {
                if (!finish[i]) {
                    printf("Process %d\n", i);
                }
            }
            return true;
        }
    }

    printf("No deadlock detected.\n");
    return false;
}

int main() {
    // Initialize allocation, maximum, and available resources
    int allocationInput[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maxInput[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int availableInput[R] = {3, 3, 2};

    // Copy inputs to global matrices
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            allocation[i][j] = allocationInput[i][j];
            max[i][j] = maxInput[i][j];
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] = availableInput[i];
    }

    // Calculate the need matrix
    calculateNeed();

    // Check for deadlock
    isDeadlocked();

    return 0;
}
