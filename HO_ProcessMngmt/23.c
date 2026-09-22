#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Orphan: Child process whose parent have terminated
// reverse of zombie process
// But orphan executes normally, unlike zombie

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child started. PID = %d\n", getpid());
        printf("My parent PID = %d\n", getppid());

        sleep(10);

        printf("After parent terminates:\n");
        printf("Child PID = %d\n", getpid());
        // pid of new parent that adopted it
        printf("New parent PID = %d\n", getppid()); 
    }
    else
    {
        // Parent process
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        sleep(2);

        printf("Parent exiting...\n");
        exit(0);
    }

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ ./a.out 
// Parent PID = 24049
// Child PID = 24050
// Child started. PID = 24050
// My parent PID = 24049
// Parent exiting...
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ After parent terminates:
// Child PID = 24050
// New parent PID = 10904
