#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Structure for the message
struct message {
    // Message type (must be > 0), 
    // used to select messsages when receiving them
    long mtype;       
    char mtext[100];  // Message text
};

int main(void)
{
    key_t key;
    int msgid;
    // format in which message should be for using msgsnd()
    struct message msg;

    // Generate a key
    key = ftok(".", 'A');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create the queue if it does not already exist
    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from the sender!");

    // Send the message to the queue
    // +1 in strlen part: to include '\0'
    // msgsnd(queue id, message struct, len of message, flags (0 -> no flag))
    if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent successfully!\n");
    printf("Message Queue ID: %d\n", msgid);
    printf("Message: %s\n", msg.mtext);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Message sent successfully!
// Message Queue ID: 1
// Message: Hello from the sender!
