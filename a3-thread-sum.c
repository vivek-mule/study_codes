// file: thread_sum.c
#include <stdio.h>
#include <pthread.h>

void* compute_sum(void* arg) {
    int* num = (int*)arg;
    int sum = 0;
    for (int i = 1; i <= *num; i++) {
        sum += i;
    }
    printf("Sum from 1 to %d = %d\n", *num, sum);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int n1 = 10, n2 = 20;

    pthread_create(&t1, NULL, compute_sum, &n1);
    pthread_create(&t2, NULL, compute_sum, &n2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads completed.\n");
    return 0;
}
