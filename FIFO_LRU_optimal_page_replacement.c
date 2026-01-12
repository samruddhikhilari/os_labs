#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

// Function to implement FIFO Page Replacement
void fifo(int pages[], int numPages, int numFrames) {
    int frame[MAX_FRAMES], pageFaults = 0, index = 0;
    for (int i = 0; i < numFrames; i++) frame[i] = -1; // Initialize frames

    for (int i = 0; i < numPages; i++) {
        int found = 0;
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is already in frame
                break;
            }
        }

        if (!found) {
            frame[index] = pages[i]; // Replace the page
            index = (index + 1) % numFrames; // Move to the next frame
            pageFaults++;
        }

        printf("FIFO Frame: ");
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// Function to implement LRU Page Replacement
void lru(int pages[], int numPages, int numFrames) {
    int frame[MAX_FRAMES], pageFaults = 0, lastUsed[MAX_FRAMES], time = 0;
    for (int i = 0; i < numFrames; i++) frame[i] = -1; // Initialize frames

    for (int i = 0; i < numPages; i++) {
        int found = 0;
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is already in frame
                lastUsed[j] = time++; // Update last used time
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 0; j < numFrames; j++) {
                if (frame[j] == -1) {
                    lruIndex = j; // Find an empty frame
                    break;
                }
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j; // Find the least recently used frame
                }
            }

            frame[lruIndex] = pages[i]; // Replace the page
            lastUsed[lruIndex] = time++;
            pageFaults++;
        }

        printf("LRU Frame: ");
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

// Function to implement Optimal Page Replacement
void optimal(int pages[], int numPages, int numFrames) {
    int frame[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < numFrames; i++) frame[i] = -1; // Initialize frames

    for (int i = 0; i < numPages; i++) {
        int found = 0;
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is already in frame
                break;
            }
        }

        if (!found) {
            int replaceIndex = -1, farthest = -1;
            for (int j = 0; j < numFrames; j++) {
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j; // Found a frame to replace
                        }
                        break;
                    }
                }
                if (k == numPages) {
                    replaceIndex = j; // Frame not used again
                    break;
                }
            }

            frame[replaceIndex] = pages[i]; // Replace the page
            pageFaults++;
        }

        printf("Optimal Frame: ");
        for (int j = 0; j < numFrames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], numPages, numFrames;

    printf("Enter number of pages: ");
    scanf("%d", &numPages);
    printf("Enter page reference string:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &numFrames);

    printf("\n--- FIFO Page Replacement ---\n");
    fifo(pages, numPages, numFrames);

    printf("\n--- LRU Page Replacement ---\n");
    lru(pages, numPages, numFrames);

    printf("\n--- Optimal Page Replacement ---\n");
    optimal(pages, numPages, numFrames);

    return 0;
}
