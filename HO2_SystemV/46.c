#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key;
    int msgid;

    // Generate the same key used to create the queue
    key = ftok(".", 'A');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the ID of the existing message queue
    msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue ID: %d\n", msgid);

    // Remove the message queue
    // IPC_RMID: command to remove queue (along with all messages)
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully!\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Message Queue ID: 1
// Message queue removed successfully!