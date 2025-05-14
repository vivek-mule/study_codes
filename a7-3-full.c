#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m; // n = number of processes, m = number of resources
int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX], available[MAX];
int safeSequence[MAX];

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

// Safety Algorithm
bool isSafe() {
    int work[MAX];
    bool finish[MAX] = {false};

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

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
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false; // System is not in a safe state
    }
    return true; // System is in a safe state
}

// Resource Request Algorithm
bool requestResources(int processID, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[processID][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Try allocating temporarily
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request granted. System remains in a safe state.\n");
        return true;
    } else {
        // Rollback
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("Request denied. System would be in unsafe state.\n");
        return false;
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
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

    int choice;
    do {
        printf("\n--- Banker's Algorithm Menu ---\n");
        printf("1. Safety Check\n");
        printf("2. Resource Request\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isSafe()) {
                    printf("System is in a safe state.\nSafe Sequence: ");
                    for (int i = 0; i < n; i++)
                        printf("P%d ", safeSequence[i]);
                    printf("\n");
                } else {
                    printf("System is NOT in a safe state.\n");
                }
                break;

            case 2: {
                int pid, request[MAX];
                printf("Enter process number (0 to %d): ", n - 1);
                scanf("%d", &pid);
                printf("Enter resources requested by P%d: ", pid);
                for (int i = 0; i < m; i++)
                    scanf("%d", &request[i]);
                requestResources(pid, request);
                break;
            }

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
