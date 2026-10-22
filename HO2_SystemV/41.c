#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> // IPC key-related definations
#include <sys/msg.h> // message queue functions

int main(void)
{
    key_t key;
    int msgid;

    // Generate a key using a file path and project ID
    //   ftok(
    //      pathname (current directory), 
    //      project identifier (just to distinguish if same path)
    //   ): unique token based on inputs 
    key = ftok(".", 'A');

    if (key == (key_t)-1) {
        perror("ftok");

        // EXIT_FAILURE: indicate program terminated unsuccessfully
        // same as exit(1) :)
        exit(EXIT_FAILURE);
    }

    // Create a message queue, or access it if it already exists
    // IPC_CREAT: requests creation of queue if necessary
    // 0666: as before, permissions (read and write for owner, group and others)
    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Print the key and message queue ID
    printf("Message Queue Key: %ld\n", (long)key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Message Queue Key: 1093675511
// Message Queue ID: 1