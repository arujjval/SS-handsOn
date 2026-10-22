#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate the same key used when creating the queue
    key = ftok(".", 'A');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the existing message queue ID
    msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Retrieve current queue information
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    // Display the current permissions
    printf("Old permissions: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    // Change permissions to owner read/write only (0600)
    // 0600 means:
    // - Owner: read and write permissions.
    // - Group: no permissions.
    // - Others: no permissions.
    info.msg_perm.mode =
        (info.msg_perm.mode & ~0777) | 0600;

    // Apply the new permissions
    // IPC_SET: command for kernel to apply modifiable queue attributes
    // from struct (does not apply to all fields)
    // necessary privileges is needed to apply this
    if (msgctl(msgid, IPC_SET, &info) == -1) {
        perror("msgctl IPC_SET");
        exit(EXIT_FAILURE);
    }

    // Retrieve the updated information
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    // Display the updated permissions
    printf("New permissions: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Old permissions: 666
// New permissions: 600
