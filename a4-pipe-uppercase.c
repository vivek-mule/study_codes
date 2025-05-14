#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int fd[2];
    int fd2[2];
    char buf[10]; 
    char buf1[10];
    char buf3[10];
    pid_t x;

    pipe(fd);
    pipe(fd2);
    x = fork();

    if (x == 0) {
        close(fd[0]); 
        write(fd[1], "five1", 6);
        close(fd[1]);

        close(fd2[1]);
        read(fd2[0], buf3, sizeof(buf3)); 
        printf("Modified msg: %s\n", buf3);
        close(fd2[0]);

    } else {
        close(fd[1]); 
        read(fd[0], buf, sizeof(buf));
        close(fd[0]);
        printf("Read msg: %s\n", buf);

        strcpy(buf1, buf); 
        to_uppercase(buf1);

        close(fd2[0]); 
        write(fd2[1], buf1, strlen(buf1) + 1);
        close(fd2[1]);
    }

    return 0;
}
