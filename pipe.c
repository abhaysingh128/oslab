#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from child!";
    char read_msg[100];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();  // Fork a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        close(fd[0]);  // Close reading end
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Write to pipe
        close(fd[1]);  // Close writing end after writing
    } else {  // Parent process
        close(fd[1]);  // Close writing end
        read(fd[0], read_msg, sizeof(read_msg));  // Read from pipe
        printf("Parent received: %s\n", read_msg);
        close(fd[0]);  // Close reading end
        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}
