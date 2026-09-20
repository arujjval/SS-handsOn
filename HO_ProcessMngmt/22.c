#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// A zombie is a child process that has finished execution 
// but whose parent has not yet collected its exit status
// parent might need its info even after child's termination
// till parent calls wait(), child remains zombie

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
        printf("Child process: PID = %d\n", getpid());
        printf("Child is exiting...\n");

        // its status will be Z+ (zombie)

        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent is sleeping for 30 seconds...\n");
        sleep(30);

        // wait(NULL): to get exit status of child process

        printf("Parent is now exiting...\n");
    }

    return 0;
}