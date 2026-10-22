#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// Structure for the message
struct message {
    long mtype;
    char mtext[100];
};

int main(void)
{
    key_t key;
    int msgid;
    struct message msg;
    ssize_t n;

    // Generate the same key used by the sender
    key = ftok(".", 'A');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Access the existing message queue
    msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // (a) Receive with flag 0: wait for a message
    printf("Receiving with flag 0...\n");

    // similar structure of msgrcv() as msgsnd()
    // msgrcv(msgid, &msg, size, message type to rcv, flags);
    n = msgrcv(msgid, &msg, sizeof(msg.mtext),
               1, 0);

    if (n == -1) {
        perror("msgrcv");
    } else {
        msg.mtext[n] = '\0';
        printf("Received message: %s\n", msg.mtext);
        printf("Message type: %ld\n", msg.mtype);
    }

    // (b) Receive with IPC_NOWAIT: do not wait
    printf("\nReceiving with IPC_NOWAIT...\n");

    n = msgrcv(msgid, &msg, sizeof(msg.mtext),
               1, IPC_NOWAIT);

    if (n == -1) {
        // no matching message available
        if (errno == ENOMSG) {
            printf("No message available. Returning immediately.\n");
        } else {
            perror("msgrcv");
        }
    } else {
        msg.mtext[n] = '\0'; // to mark end of string for printf()
        printf("Received message: %s\n", msg.mtext);
        printf("Message type: %ld\n", msg.mtype);
    }

    return 0;
}

// OUTPUT: 
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Receiving with flag 0...
// Received message: Hello from the sender!
// Message type: 1

// Receiving with IPC_NOWAIT...
// No message available. Returning immediately.