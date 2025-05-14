#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sort_ascending(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort_descending(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];  // VLA (Variable Length Array)

    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }
    else if(pid == 0) {
        // Child process: Ascending sort
        printf("\nChild process: Sorting in ascending order:\n");
        sort_ascending(arr, n);
        for(int i=0; i<n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else {
        // Parent process: Descending sort
        printf("\nParent process: Sorting in descending order:\n");
        sort_descending(arr, n);
        for(int i=0; i<n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}