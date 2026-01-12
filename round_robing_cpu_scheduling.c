#include <stdio.h>

struct Process {
    int id;        // Process ID
    int burst;     // Burst time
    int remaining; // Remaining time
    int arrival;   // Arrival time
};

void roundRobin(struct Process proc[], int n, int quantum) {
    int waitingTime[n], turnaroundTime[n];
    int time = 0, completed = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
    }

    // Round Robin Scheduling
    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (proc[i].remaining > 0 && proc[i].arrival <= time) {
                executed = 1;

                if (proc[i].remaining > quantum) {
                    // Process runs for the quantum time
                    time += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    // Process finishes execution
                    time += proc[i].remaining;
                    waitingTime[i] = time - proc[i].burst - proc[i].arrival;
                    turnaroundTime[i] = time - proc[i].arrival;
                    proc[i].remaining = 0;
                    completed++;
                }
            }
        }

        if (!executed) {
            // If no process was executed, move time forward
            time++;
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
        {1, 10, 0},
        {2, 5, 1},
        {3, 8, 2}
    };

    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 3; // Define the time quantum
    roundRobin(proc, n, quantum);

    return 0;
}
