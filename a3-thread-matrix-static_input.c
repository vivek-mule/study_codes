#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 4  // Define matrix size (for simplicity, using 4x4 matrices)

// Structure to hold the arguments for each thread
typedef struct {
    int row;
    int col;
    int (*A)[MAX];
    int (*B)[MAX];
    int (*C)[MAX];
} ThreadArgs;

// Function to multiply matrices and store the result in C
void* multiply(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int sum = 0;
    
    // Perform the row-column multiplication
    for (int i = 0; i < MAX; i++) {
        sum += args->A[args->row][i] * args->B[i][args->col];
    }
    
    // Store the result in C matrix
    args->C[args->row][args->col] = sum;

    pthread_exit(NULL);
}

int main() {
    // Example matrices A and B
    int A[MAX][MAX] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int B[MAX][MAX] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    // Result matrix
    int C[MAX][MAX] = {0};

    // Array to hold thread IDs
    pthread_t threads[MAX][MAX];
    ThreadArgs args[MAX][MAX];

    // Create threads to perform multiplication
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            args[i][j].row = i;
            args[i][j].col = j;
            args[i][j].A = A;
            args[i][j].B = B;
            args[i][j].C = C;

            // Create a new thread to calculate the element (i, j)
            pthread_create(&threads[i][j], NULL, multiply, (void*)&args[i][j]);
        }
    }

    // Wait for all threads to complete and collect results
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads[i][j], NULL);  // Collect the results
        }
    }

    // Print the resulting matrix
    printf("Resulting Matrix C:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
