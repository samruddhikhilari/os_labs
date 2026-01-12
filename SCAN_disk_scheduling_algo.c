#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 200 // Assuming a maximum of 200 tracks

// Function to implement SCAN Disk Scheduling
void scan(int requests[], int numRequests, int head, int direction)
{
    int seekSequence[MAX_TRACKS];
    int distance, totalSeek = 0, index = 0;

    // Create a temporary array to store sorted requests
    int temp[MAX_TRACKS], tempIndex = 0;
    for (int i = 0; i < numRequests; i++)
    {
        temp[tempIndex++] = requests[i];
    }

    // Sort requests
    for (int i = 0; i < tempIndex; i++)
    {
        for (int j = i + 1; j < tempIndex; j++)
        {
            if (temp[i] > temp[j])
            {
                int tempVal = temp[i];
                temp[i] = temp[j];
                temp[j] = tempVal;
            }
        }
    }

    // Add the head position to the array
    int totalTracks = 0;
    if (direction == 1)
    { // Moving right
        for (int i = 0; i < tempIndex; i++)
        {
            if (temp[i] >= head)
            {
                seekSequence[totalTracks++] = head;
                for (int j = i; j < tempIndex; j++)
                {
                    seekSequence[totalTracks++] = temp[j];
                }
                seekSequence[totalTracks++] = MAX_TRACKS - 1; // Go to the end
                for (int j = i - 1; j >= 0; j--)
                {
                    seekSequence[totalTracks++] = temp[j];
                }
                break;
            }
        }
    }
    else
    { // Moving left
        for (int i = tempIndex - 1; i >= 0; i--)
        {
            if (temp[i] <= head)
            {
                seekSequence[totalTracks++] = head;
                for (int j = i; j >= 0; j--)
                {
                    seekSequence[totalTracks++] = temp[j];
                }
                seekSequence[totalTracks++] = 0; // Go to the beginning
                for (int j = i + 1; j < tempIndex; j++)
                {
                    seekSequence[totalTracks++] = temp[j];
                }
                break;
            }
        }
    }

    // Calculate total seek time
    for (int i = 0; i < totalTracks - 1; i++)
    {
        distance = abs(seekSequence[i + 1] - seekSequence[i]);
        totalSeek += distance;
    }

    printf("SCAN Seek Sequence: ");
    for (int i = 0; i < totalTracks; i++)
    {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time (SCAN): %d\n", totalSeek);
}

int main()
{
    int requests[MAX_TRACKS], numRequests, head, direction;

    printf("Enter number of requests: ");
    scanf("%d", &numRequests);
    printf("Enter the request sequence:\n");
    for (int i = 0; i < numRequests; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    printf("\n--- SCAN Disk Scheduling ---\n");
    scan(requests, numRequests, head, direction);

    return 0;
}
