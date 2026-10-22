#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

// Shared data
struct shared_data {
    int ticket_number;
    int shared_value;
};

// Required for semctl() on Linux
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Perform semaphore operation
void semaphore_op(int semid, unsigned short sem_num, short op)
{
    struct sembuf sb;

    sb.sem_num = sem_num;
    sb.sem_op = op;
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        _exit(EXIT_FAILURE);
    }
}

int main(void)
{
    int semid, shmid;
    struct shared_data *data;
    unsigned short initial_values[2] = {1, 2};
    union semun arg;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared_data),
                   IPC_CREAT | 0600);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    data = (struct shared_data *)shmat(shmid, NULL, 0);

    if (data == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    data->ticket_number = 0;
    data->shared_value = 0;

    // Create a set containing two semaphores
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);

    if (semid == -1) {
        perror("semget");
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    // Semaphore 0 = mutex (initial value 1)
    // Semaphore 1 = counting semaphore (initial value 2)
    arg.array = initial_values;

    if (semctl(semid, 0, SETALL, arg) == -1) {
        perror("semctl SETALL");
        semctl(semid, 0, IPC_RMID);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    printf("Semaphore set created. ID = %d\n", semid);
    printf("Mutex value = 1, Counting semaphore value = 2\n\n");
    fflush(stdout);

    // Create three processes
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            break;
        }

        if (pid == 0) {
            // (a) Protect ticket number creation
            for (int j = 0; j < 2; j++) {
                // P operation: acquire mutex
                semaphore_op(semid, 0, -1);

                data->ticket_number++;
                data->shared_value = data->ticket_number;

                printf("PID %ld: Ticket = %d, Shared value = %d\n",
                       (long)getpid(),
                       data->ticket_number,
                       data->shared_value);
                fflush(stdout);

                // V operation: release mutex
                semaphore_op(semid, 0, 1);
            }

            // (c) Acquire one of two available resources
            semaphore_op(semid, 1, -1);

            printf("PID %ld acquired a resource\n", (long)getpid());
            fflush(stdout);

            sleep(1);  // Simulate using the resource

            printf("PID %ld released the resource\n", (long)getpid());
            fflush(stdout);

            // Return the resource
            semaphore_op(semid, 1, 1);

            shmdt(data);
            _exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes
    while (wait(NULL) > 0)
        ;

    printf("\nFinal ticket number = %d\n", data->ticket_number);
    printf("Final shared value = %d\n", data->shared_value);

    // (d) Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
    } else {
        printf("Semaphore set removed successfully.\n");
    }

    // Detach and remove shared memory
    if (shmdt(data) == -1)
        perror("shmdt");

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        perror("shmctl IPC_RMID");
    else
        printf("Shared memory removed successfully.\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Semaphore set created. ID = 3
// Mutex value = 1, Counting semaphore value = 2

// PID 120901: Ticket = 1, Shared value = 1
// PID 120901: Ticket = 2, Shared value = 2
// PID 120901 acquired a resource
// PID 120902: Ticket = 3, Shared value = 3
// PID 120902: Ticket = 4, Shared value = 4
// PID 120902 acquired a resource
// PID 120903: Ticket = 5, Shared value = 5
// PID 120903: Ticket = 6, Shared value = 6
// PID 120901 released the resource
// PID 120903 acquired a resource
// PID 120902 released the resource
// PID 120903 released the resource

// Final ticket number = 6
// Final shared value = 6
// Semaphore set removed successfully.
// Shared memory removed successfully.