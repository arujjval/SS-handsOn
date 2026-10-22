#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Required for semctl() on many Linux systems
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(void)
{
    key_t key;
    int binary_sem, counting_sem;
    union semun arg;

    // Generate a key
    key = ftok(".", 'S');

    if (key == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // (a) Create a binary semaphore
    // semget(
    //  semaphore set, 
    //  no. of semaphore in set, 
    //  flags): create semaphore
    // IPC_CREAT: create if does not exist, 0666: permissions
    binary_sem = semget(key, 1, IPC_CREAT | 0666);

    if (binary_sem == -1) {
        perror("semget binary");
        exit(EXIT_FAILURE);
    }

    // Initialize binary semaphore to 1
    arg.val = 1;

    // semctl: fcntl() type for semaphore
    // semctl(
    //  semaphore set ID, 
    //  semaphore index (0-indexed), 
    //  command (SETVAl: to set value), 
    //  semun (union to give inputs))
    if (semctl(binary_sem, 0, SETVAL, arg) == -1) {
        perror("semctl binary");
        exit(EXIT_FAILURE);
    }

    printf("Binary semaphore created successfully.\n");
    printf("Binary semaphore ID: %d\n", binary_sem);
    printf("Initial value: 1\n");

    // Generate a different key for the counting semaphore
    key = ftok(".", 'C');

    if (key == (key_t)-1) {
        perror("ftok counting");
        exit(EXIT_FAILURE);
    }

    // Create a counting semaphore
    counting_sem = semget(key, 1, IPC_CREAT | 0666);

    if (counting_sem == -1) {
        perror("semget counting");
        exit(EXIT_FAILURE);
    }

    // Initialize counting semaphore to 5
    arg.val = 5;

    if (semctl(counting_sem, 0, SETVAL, arg) == -1) {
        perror("semctl counting");
        exit(EXIT_FAILURE);
    }

    printf("\nCounting semaphore created successfully.\n");
    printf("Counting semaphore ID: %d\n", counting_sem);
    printf("Initial value: 5\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Binary semaphore created successfully.
// Binary semaphore ID: 0
// Initial value: 1

// Counting semaphore created successfully.
// Counting semaphore ID: 1
// Initial value: 5