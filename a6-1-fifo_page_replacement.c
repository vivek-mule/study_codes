#include <stdio.h>

#define MAX 100

int isInMemory(int page, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++)
        if (frames[i] == page)
            return i;
    return -1;
}

int main() {
    int pages[MAX], n, frameCount, pageFaults = 0;
    int frames[MAX], front = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

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
            printf("%s%d", j ? " " : "", frames[j] != -1 ? frames[j] : -1);
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
    return 0;
}
