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

            if (replaceIndex == -1)
                replaceIndex = 0;

            frames[replaceIndex] = page;
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
