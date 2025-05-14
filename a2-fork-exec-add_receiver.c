#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    if (argc < 3)
    {
        printf("Insufficient arguments\n");
        exit(-1);
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int sum = num1 + num2;
    printf("Sum of %d and %d is %d\n", num1, num2, sum);
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    exit(0);
    
}