#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGSTOP caught!\n");
}

int main(void)
{
    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for SIGSTOP...\n");
    fflush(stdout);

    // handler won't run because SIGSTOP cannot be caught, blocked or ignored.
    // OS directly handles this signal. 
    // SIGSTOP: stops the process (suspended temporarily). 
    signal(SIGSTOP, handler);

    while (1)
    {
        sleep(1);
    }

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/64$ ./receiver 
// Receiver PID: 118364
// Waiting for SIGSTOP...

// [2]+  Stopped                 ./receiver