#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 200 // Assuming a maximum of 200 tracks

// Function to implement C-SCAN Disk Scheduling
void cscan(int requests[], int numRequests, int head) {
    int seekSequence[MAX_TRACKS];
    int distance, totalSeek = 0, index = 0;

    // Create a temporary array to store sorted requests
    int temp[MAX_TRACKS], tempIndex = 0;
    for (int i = 0; i < numRequests; i++) {
        temp[tempIndex++] = requests[i];
    }

    // Sort requests
    for (int i = 0; i < tempIndex; i++) {
        for (int j = i + 1; j < tempIndex; j++) {
            if (temp[i] > temp[j]) {
                int tempVal = temp[i];
                temp[i] = temp[j];
                temp[j] = tempVal;
            }
        }
    }

    // Add the head position to the array
    int totalTracks = 0;
    seekSequence[totalTracks++] = head;

    // Move to the right first
    for (int i = 0; i < tempIndex; i++) {
        if (temp[i] >= head) {
            seekSequence[totalTracks++] = temp[i];
        }
    }

    // Jump to the end
    seekSequence[totalTracks++] = MAX_TRACKS - 1; // Go to the end

    // Continue from the beginning to the head
    for (int i = 0; i < tempIndex; i++) {
        if (temp[i] < head) {
            seekSequence[totalTracks++] = temp[i];
        }
    }

    // Calculate total seek time
    for (int i = 0; i < totalTracks - 1; i++) {
        distance = abs(seekSequence[i + 1] - seekSequence[i]);
        totalSeek += distance;
    }

    printf("C-SCAN Seek Sequence: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time (C-SCAN): %d\n", totalSeek);
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

    printf("\n--- C-SCAN Disk Scheduling ---\n");
    cscan(requests, numRequests, head);

    return 0;
}
