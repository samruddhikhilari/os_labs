#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BLOCKS 10 // Maximum number of blocks
#define MIN_BLOCK_SIZE 16 // Minimum block size

typedef struct Block {
    int size;
    int free;
    struct Block *next;
} Block;

Block *freeList = NULL;

// Function to initialize the memory
void initializeMemory(int totalSize) {
    if (totalSize < MIN_BLOCK_SIZE) {
        printf("Total size must be at least %d bytes.\n", MIN_BLOCK_SIZE);
        return;
    }

    freeList = (Block *)malloc(sizeof(Block));
    freeList->size = totalSize;
    freeList->free = 1; // Mark as free
    freeList->next = NULL;
}

// Function to split a block into two buddies
void splitBlock(Block *block) {
    if (block->size <= MIN_BLOCK_SIZE) {
        return;
    }

    Block *buddy = (Block *)((char *)block + block->size / 2);
    buddy->size = block->size / 2;
    buddy->free = 1;
    buddy->next = block->next;

    block->size = block->size / 2;
    block->next = buddy;
}

// Function to merge two buddies
void mergeBlocks(Block *block) {
    Block *nextBlock = (Block *)((char *)block + block->size);
    if (nextBlock && nextBlock->free) {
        block->size += nextBlock->size;
        block->next = nextBlock->next; // Remove nextBlock from free list
        free(nextBlock);
    }
}

// Function to allocate memory
void *allocateMemory(int size) {
    Block *current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            while (current->size > size) {
                splitBlock(current);
            }
            current->free = 0; // Mark as allocated
            return (void *)((char *)current + sizeof(Block)); // Return pointer to usable memory
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

// Function to free memory
void freeMemory(void *ptr) {
    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->free = 1; // Mark as free
    mergeBlocks(block); // Merge with buddy if possible
}

// Function to display the free list
void displayFreeList() {
    Block *current = freeList;
    printf("Free List:\n");
    while (current) {
        printf("Block size: %d, Status: %s\n", current->size, current->free ? "Free" : "Allocated");
        current = current->next;
    }
}

int main() {
    int totalSize;

    printf("Enter total memory size (must be >= %d): ", MIN_BLOCK_SIZE);
    scanf("%d", &totalSize);

    initializeMemory(totalSize);

    // Sample allocations
    void *ptr1 = allocateMemory(20);
    printf("Allocated 20 bytes at %p\n", ptr1);
    displayFreeList();

    void *ptr2 = allocateMemory(30);
    printf("Allocated 30 bytes at %p\n", ptr2);
    displayFreeList();

    freeMemory(ptr1);
    printf("Freed 20 bytes at %p\n", ptr1);
    displayFreeList();

    void *ptr3 = allocateMemory(10);
    printf("Allocated 10 bytes at %p\n", ptr3);
    displayFreeList();

    freeMemory(ptr2);
    printf("Freed 30 bytes at %p\n", ptr2);
    displayFreeList();

    freeMemory(ptr3);
    printf("Freed 10 bytes at %p\n", ptr3);
    displayFreeList();

    // Cleanup
    free(freeList);

    return 0;
}
