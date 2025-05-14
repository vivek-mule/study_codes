#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // In child process: replace with "ls -l"
        printf("Child process replacing itself with 'ls -l'\n");
        execl("/bin/ls", "ls", "-l", NULL);

        // If exec fails
        perror("exec failed");
        return 1;
    }
    else {
        // In parent process
        printf("Parent process: waiting for child...\n");
        wait(NULL);
        printf("Child process finished.\n");
    }

    return 0;
}