#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> // msqid_ds
#include <time.h>

int main(void)
{
    int msgid;

    // msqid_ds: stores info about System V message queue
    struct msqid_ds info;

    // Enter the message queue ID
    printf("Enter Message Queue ID: ");
    if (scanf("%d", &msgid) != 1) {
        fprintf(stderr, "Invalid message queue ID\n");
        return 1;
    }

    // Get information about the message queue
    // msgctl(): almost like fcntl() for message queues, control on queue
    // IPC_STAT: command for msgctl() for getting message queue stats
    if (msgctl(msgid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    printf("\n--- Message Queue Information ---\n");

    // a. Access permissions
    // msg_perm: ownerships and permissions of queue
    // .mode: permission bits and other bits too
    // 0777: bit mask to retrieve standard permission bits from .mode
    printf("Access Permissions : %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    // b. User ID and Group ID
    // Linux compares process credentials with the resource's ownership 
    // and permission settings, then allows or denies the requested operation.
    printf("UID                : %u\n",
           (unsigned int)info.msg_perm.uid);
    printf("GID                : %u\n",
           (unsigned int)info.msg_perm.gid);

    // c. Time of last message sent and received
    printf("Last Message Sent  : %s",
           info.msg_stime == 0 ? "Never\n" :
           ctime(&info.msg_stime));

    printf("Last Message Recv  : %s",
           info.msg_rtime == 0 ? "Never\n" :
           ctime(&info.msg_rtime));

    // d. Time of last change to the queue
    printf("Last Queue Change  : %s",
           info.msg_ctime == 0 ? "Never\n" :
           ctime(&info.msg_ctime));

    // e. Current size of the queue in bytes
    printf("Current Queue Size : %lu bytes\n",
           (unsigned long)info.msg_cbytes);

    // f. Number of messages in the queue
    printf("Number of Messages : %lu\n",
           (unsigned long)info.msg_qnum);

    // g. Maximum number of bytes allowed in the queue
    printf("Maximum Queue Size : %lu bytes\n",
           (unsigned long)info.msg_qbytes);

    // h. Process IDs of last sender and receiver
    printf("Last Sender PID    : %d\n",
           (int)info.msg_lspid);
    printf("Last Receiver PID  : %d\n",
           (int)info.msg_lrpid);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Enter Message Queue ID: 1

// --- Message Queue Information ---
// Access Permissions : 666
// UID                : 1000
// GID                : 1000
// Last Message Sent  : Never
// Last Message Recv  : Never
// Last Queue Change  : Thu Oct 22 14:31:35 2026
// Current Queue Size : 0 bytes
// Number of Messages : 0
// Maximum Queue Size : 16384 bytes
// Last Sender PID    : 0
// Last Receiver PID  : 0