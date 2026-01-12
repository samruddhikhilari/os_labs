#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 200 // Assuming a maximum of 200 tracks

// Function to implement SSTF Disk Scheduling
void sstf(int requests[], int numRequests, int head) {
    int seekSequence[MAX_TRACKS];
    int visited[MAX_TRACKS] = {0}; // To keep track of visited requests
    int totalSeek = 0;

    int currentHead = head;
    int totalTracks = 0;

    for (int i = 0; i < numRequests; i++) {
        int minDistance = 1000; // Initialize to a large value
        int minIndex = -1;

        // Find the closest request
        for (int j = 0; j < numRequests; j++) {
            if (!visited[j]) { // If request is not yet visited
                int distance = abs(requests[j] - currentHead);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = j;
                }
            }
        }

        // Visit the closest request
        visited[minIndex] = 1;
        seekSequence[totalTracks++] = requests[minIndex];
        totalSeek += minDistance;
        currentHead = requests[minIndex];
    }

    // Print the seek sequence and total seek time
    printf("SSTF Seek Sequence: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time (SSTF): %d\n", totalSeek);
}

int main() {
    int requests[MAX_TRACKS], numRequests, head;

    printf("Enter number of requests: ");
    scanf("%d", &numRequests);
    printf("Enter the request sequence:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\n--- SSTF Disk Scheduling ---\n");
    sstf(requests, numRequests, head);

    return 0;
}
