#include <stdio.h>

struct Process {
    int id;        // Process ID
    int burst;     // Burst time
    int arrival;   // Arrival time
};

void sjfNonPreemptive(struct Process proc[], int n) {
    int waitingTime[n], turnaroundTime[n];
    int completed[n];
    int time = 0, completedCount = 0;

    // Initialize completed array
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    while (completedCount < n) {
        int minIndex = -1;
        int minBurst = 9999; // A large number to find the minimum

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= time && !completed[i] && proc[i].burst < minBurst) {
                minBurst = proc[i].burst;
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            time += proc[minIndex].burst; // Execute the selected process
            completed[minIndex] = 1;
            completedCount++;

            // Calculate waiting and turnaround times
            waitingTime[minIndex] = time - proc[minIndex].arrival - proc[minIndex].burst;
            turnaroundTime[minIndex] = time - proc[minIndex].arrival;
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
    sjfNonPreemptive(proc, n);

    return 0;
}
