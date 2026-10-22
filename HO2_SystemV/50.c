#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void semaphore_op(int semid, int sem_num, int operation)
{
    struct sembuf sb;

    sb.sem_num = sem_num;
    sb.sem_op = operation;
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        _exit(EXIT_FAILURE);
    }
}

int main(void)
{
    int semid;
    unsigned short values[2] = {1, 1};
    union semun arg;

    // Create two semaphores, both initialized to 1
    // IPC_PRIVATE: request new IPC object instead of looking up 
    // using a shared key
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);

    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    arg.array = values;

    if (semctl(semid, 0, SETALL, arg) == -1) {
        perror("semctl");
        semctl(semid, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }

    printf("Two semaphores created.\n");
    printf("Starting intentional deadlock...\n");

    // to send buffered output to the terminal right away
    // to remove that possibility of parent and child shows same output twice
    fflush(stdout);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        semctl(semid, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Process P2
        printf("P2: Locking Semaphore 2...\n");
        fflush(stdout);
        semaphore_op(semid, 1, -1);

        sleep(1);

        printf("P2: Waiting for Semaphore 1...\n");
        fflush(stdout);
        semaphore_op(semid, 0, -1);  // Blocks forever

        _exit(EXIT_SUCCESS);
    } else {
        // Process P1
        printf("P1: Locking Semaphore 1...\n");
        fflush(stdout);
        semaphore_op(semid, 0, -1);

        sleep(1);

        printf("P1: Waiting for Semaphore 2...\n");
        fflush(stdout);
        semaphore_op(semid, 1, -1);  // Blocks forever

        wait(NULL);
    }

    // Normally unreachable because of the deadlock
    semctl(semid, 0, IPC_RMID);
    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Two semaphores created.
// Starting intentional deadlock...
// P1: Locking Semaphore 1...
// P2: Locking Semaphore 2...
// P1: Waiting for Semaphore 2...
// P2: Waiting for Semaphore 1...



