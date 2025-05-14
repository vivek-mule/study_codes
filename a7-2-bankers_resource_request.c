#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;
int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX], available[MAX];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool isSafe() {
    int work[MAX];
    bool finish[MAX] = {false};
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool requestResources(int pid, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[pid][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request granted. System remains in a safe state.\n");
        return true;
    } else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    calculateNeed();

    int pid, request[MAX];
    printf("Enter Process ID (0 to %d): ", n - 1);
    scanf("%d", &pid);

    printf("Enter Request for Process P%d:\n", pid);
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    requestResources(pid, request);

    return 0;
}
