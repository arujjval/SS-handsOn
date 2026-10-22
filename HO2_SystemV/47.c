#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(void)
{
    key_t key;
    int shmid;
    char *ptr;

    // Generate a key for shared memory
    key = ftok(".", 'S');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment of 1024 bytes
    // shmget(key, ,flags/permissions)
    shmid = shmget(key, 1024, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory created. ID = %d\n", shmid);

    // (a) Attach with read-write access
    ptr = (char *)shmat(shmid, NULL, 0);

    if (ptr == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write data to shared memory
    strcpy(ptr, "Hello from shared memory!");

    printf("Data written: %s\n", ptr);

    // (b) Detach the read-write attachment
    if (shmdt(ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Attach in read-only mode
    ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);

    if (ptr == (void *)-1) {
        perror("shmat read-only");
        exit(EXIT_FAILURE);
    }

    printf("Read-only attachment successful.\n");
    printf("Data read: %s\n", ptr);

    // Attempting to write through this pointer is prohibited.
    // Do NOT try strcpy(ptr, "New data") here:
    // it can cause a segmentation fault.

    printf("Cannot safely overwrite data through a read-only attachment.\n");

    // (c) Detach shared memory
    if (shmdt(ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory detached.\n");

    // (d) Remove the shared memory segment
    // shmctl(): another system call for shared m. as fcntl() for files
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory marked for removal.\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Shared memory created. ID = 0
// Data written: Hello from shared memory!
// Read-only attachment successful.
// Data read: Hello from shared memory!
// Cannot safely overwrite data through a read-only attachment.
// Shared memory detached.
// Shared memory marked for removal.
