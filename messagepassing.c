#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    pid_t pid;
    key_t key;
    int msgid;

    key = ftok("progfile", 65);  // Create unique key
    msgid = msgget(key, 0666 | IPC_CREAT);  // Create message queue

    pid = fork();

    if (pid == 0) {  // Child process
        struct message msg;
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello from child!");

        msgsnd(msgid, &msg, sizeof(msg), 0);  // Send message
        printf("Message sent from child.\n");
    } else {  // Parent process
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);  // Receive message
        printf("Parent received: %s\n", msg.msg_text);

        msgctl(msgid, IPC_RMID, NULL);  // Destroy message queue
    }

    return 0;
}
