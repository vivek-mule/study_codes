#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10  // Max number of processes
#define MAX_R 10  // Max number of resources

int n, m;  // n = processes, m = resources
int allocation[MAX_P][MAX_R];
int max[MAX_P][MAX_R];
int need[MAX_P][MAX_R];
int available[MAX_R];
int safeSeq[MAX_P];

// Function to input data
void input() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources (%d):\n", m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
}

// Function to calculate the Need matrix
void calculateNeed() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check system safety and find safe sequence
bool isSafe() {
    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int count = 0;

    // Initialize work with available
    for(int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while(count < n) {
        bool found = false;
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                bool canRun = true;
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if(canRun) {
                    for(int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found) {
            return false;  // System is not in safe state
        }
    }

    return true;  // System is in safe state
}

// Function to display safe sequence
void displaySafeSequence() {
    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
}

int main() {
    input();
    calculateNeed();

    if(isSafe()) {
        displaySafeSequence();
    } else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
}
