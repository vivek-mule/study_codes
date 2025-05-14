#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t x;

    x= fork();
    if (x==0)
    {
        printf("Child Process");
        execl("execdemoadd", "execdemoadd", "5", "6", (char*)0);
        printf("End Process");
    } else {
        printf("Parent Process");
    }
    return 0;
    
}