#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char sentence[100];
    int count = 0;

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin); // Take input

    pid_t pid = vfork(); // Create child process using vfork

    if (pid < 0) {
        perror("vfork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        for (int i = 0; sentence[i] != '\0'; i++) {
            char ch = sentence[i];
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
                count++;
            }
        }
        printf("Number of vowels: %d\n", count);
        _exit(0); // Use _exit() with vfork
    } else {
        // Parent process does nothing, just exits
        wait(NULL);
    }

    return 0;
}