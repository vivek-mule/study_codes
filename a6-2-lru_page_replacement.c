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
    int frames[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

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
            printf("%s%d", j ? " " : "", frames[j] != -1 ? frames[j] : -1);
        printf("]\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
    return 0;
}
