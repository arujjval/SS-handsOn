#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Child process */
        printf("Child: PID = %d\n", getpid());
        printf("Child: Parent PID = %d\n", getppid());

        sleep(2);

        /* Send SIGKILL to the parent */
        printf("Child: Sending SIGKILL to parent...\n");
        fflush(stdout);

        // int kill(
        // pid_t pid: target process or group of processes, 
        // int sig: signal to send
        // ): to send a signal to a process; 0-> success, -1: error
        if (kill(getppid(), SIGKILL) == -1)
        {
            perror("kill failed");
            exit(1);
        }

        sleep(2);

        /* Display the new parent PID */
        printf("Child: I am now an orphan.\n");
        printf("Child: New Parent PID = %d\n", getppid());
    }
    else
    {
        /* Parent process */
        printf("Parent: PID = %d\n", getpid());
        printf("Parent: Child PID = %d\n", pid);

        while (1)
        {
            // When this gets SIGKILL signal, the process will terminate
            sleep(1);
        }
    }

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Parent: PID = 117405
// Child: PID = 117406
// Parent: Child PID = 117406
// Child: Parent PID = 117405
// Child: Sending SIGKILL to parent...
// Killed
// arujjval@arujjval:~/SS/HO2_SystemV$ Child: I am now an orphan.
// Child: New Parent PID = 597
