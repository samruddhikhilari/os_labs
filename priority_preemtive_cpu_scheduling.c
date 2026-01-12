#include <stdio.h>

struct Process {
    int id;        // Process ID
    int burst;     // Burst time
    int priority;  // Priority
};

void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by priority (lower number = higher priority)
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void priorityScheduling(struct Process proc[], int n) {
    sortProcesses(proc, n);

    int waitingTime[n];
    int turnaroundTime[n];

    // Calculate waiting time
    waitingTime[0] = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + proc[i - 1].burst;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + proc[i].burst;
    }

    // Print the results
    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].id, proc[i].burst, proc[i].priority, 
               waitingTime[i], turnaroundTime[i]);
    }
}

int main() {
    struct Process proc[] = {
        {1, 10, 2},
        {2, 5, 1},
        {3, 8, 3}
    };

    int n = sizeof(proc) / sizeof(proc[0]);
    priorityScheduling(proc, n);

    return 0;
}
