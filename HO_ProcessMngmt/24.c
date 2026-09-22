#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> // exit()

int main()
{
    pid_t child1, child2, child3;

    // Create first child
    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        exit(1);
    }

    // Create second child
    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(4);
        exit(2);
    }

    // Create third child
    child3 = fork();

    if (child3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(6);
        exit(3);
    }

    // Parent
    printf("Parent: PID = %d\n", getpid());

    printf("Waiting for Child 2...\n");

    // waitpid(pid wanna track, (int) to save exit status, options)
    // 0 option: block till specific child terminates ie. child2
    // Parents gets blocked till child2 terminates
    int status;
    waitpid(child2, &status, 0);

    printf("Child 2 has terminated with %d exit status.\n", 
            WEXITSTATUS(status));

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ ./a.out 
// Child 1: PID = 24426
// Child 2: PID = 24427
// Parent: PID = 24425
// Waiting for Child 2...
// Child 3: PID = 24428
// Child 2 has terminated with 2 exit status.