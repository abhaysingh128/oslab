#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);  // Create shared memory

    pid_t pid = fork();

    if (pid == 0) {  // Child process
        char *str = (char *) shmat(shmid, (void *) 0, 0);  // Attach to memory
        strcpy(str, "Hello from child!");  // Write to shared memory
        shmdt(str);  // Detach from memory
    } else {  // Parent process
        wait(NULL);  // Wait for child process
        char *str = (char *) shmat(shmid, (void *) 0, 0);  // Attach to memory
        printf("Parent received: %s\n", str);  // Read from shared memory
        shmdt(str);  // Detach from memory
        shmctl(shmid, IPC_RMID, NULL);  // Destroy shared memory
    }

    return 0;
}
