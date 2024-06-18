#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID (from child): %d\n", getppid());
        // Simulate some work in child process
        sleep(2);
        printf("Child process is done.\n");
    } else { // Parent process
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID (from parent): %d\n", pid);

        // Wait for child to complete
        wait(NULL);
        printf("Child process completed. Parent process is done.\n");
    }

    return 0;
}
