#include <stdio.h>

struct Process {
    int id;        // Process ID
    int burst;     // Burst time
    int remaining; // Remaining time
    int arrival;   // Arrival time
};

void sjfPreemptive(struct Process proc[], int n) {
    int time = 0, completed = 0;
    int waitingTime[n], turnaroundTime[n];
    int shortestIndex;

    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
    }

    while (completed < n) {
        shortestIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining > 0 && proc[i].arrival <= time) {
                if (shortestIndex == -1 || proc[i].remaining < proc[shortestIndex].remaining) {
                    shortestIndex = i;
                }
            }
        }

        if (shortestIndex != -1) {
            // Execute the selected process
            proc[shortestIndex].remaining--;
            time++;

            // If process is completed
            if (proc[shortestIndex].remaining == 0) {
                completed++;
                waitingTime[shortestIndex] = time - proc[shortestIndex].burst - proc[shortestIndex].arrival;
                turnaroundTime[shortestIndex] = time - proc[shortestIndex].arrival;
            }
        } else {
            time++; // No process is ready to execute
        }
    }

    // Print the results
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].id, proc[i].burst, waitingTime[i], turnaroundTime[i]);
    }
}

int main() {
    struct Process proc[] = {
        {1, 6, 0},
        {2, 8, 1},
        {3, 7, 2}
    };

    int n = sizeof(proc) / sizeof(proc[0]);
    sjfPreemptive(proc, n);

    return 0;
}
