#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Function to check if page is in memory
int isInMemory(int page, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++)
        if (frames[i] == page)
            return i;
    return -1;
}

// FIFO Algorithm
void fifo(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int front = 0, pageFaults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        if (isInMemory(page, frames, frameCount) == -1) {
            frames[front] = page;
            front = (front + 1) % frameCount;
            pageFaults++;
        }

        printf("Page %d => [", page);
        for (int j = 0; j < frameCount; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("_ ");
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

// LRU Algorithm
void lru(int pages[], int n, int frameCount) {
    int frames[frameCount], recent[MAX];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n--- LRU Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int index = isInMemory(page, frames, frameCount);

        if (index == -1) {
            int lruIndex = -1, lruAge = i;
            for (int j = 0; j < frameCount; j++) {
                int lastUsed = -1;
                for (int k = i - 1; k >= 0; k--) {
                    if (frames[j] == pages[k]) {
                        lastUsed = k;
                        break;
                    }
                }
                if (lastUsed == -1) {
                    lruIndex = j;
                    break;
                }
                if (lastUsed < lruAge) {
                    lruAge = lastUsed;
                    lruIndex = j;
                }
            }
            frames[lruIndex] = page;
            pageFaults++;
        }

        printf("Page %d => [", page);
        for (int j = 0; j < frameCount; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("_ ");
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

// Optimal Algorithm
void optimal(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int index = isInMemory(page, frames, frameCount);

        if (index == -1) {
            int replaceIndex = -1, farthest = i;

            for (int j = 0; j < frameCount; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1) replaceIndex = 0;

            frames[replaceIndex] = page;
            pageFaults++;
        }

        printf("Page %d => [", page);
        for (int j = 0; j < frameCount; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("_ ");
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX], n, frameCount, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    do {
        printf("\nPage Replacement Algorithms\n");
        printf("1. FIFO\n2. LRU\n3. Optimal\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, frameCount);
                break;
            case 2:
                lru(pages, n, frameCount);
                break;
            case 3:
                optimal(pages, n, frameCount);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 0);

    return 0;
}
