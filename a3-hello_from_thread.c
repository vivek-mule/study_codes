// file: thread_hello.c
#include <stdio.h>
#include <pthread.h>

void* print_hello(void* arg) {
    printf("Hello from thread! Thread ID: %p\n", (void*)pthread_self());  // Use %p for pointers
    return NULL;
}

int main() {
    pthread_t thread;

    // Create a new thread
    if (pthread_create(&thread, NULL, print_hello, NULL)) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    printf("Thread has finished execution.\n");
    return 0;
}
