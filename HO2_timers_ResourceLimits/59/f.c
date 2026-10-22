#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGVTALRM\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer = {0};
    volatile unsigned long counter = 0;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 2;

    printf("Virtual timer set for 2 seconds of user CPU time...\n");
    fflush(stdout);

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    // Here, busy loop is neede since when using pause()/sleep(),
    // its not executing user-mode instructions, so virtual timer does not
    // advance. Busy loop keep the process exeucting
    while (1)
        counter++;

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Virtual timer set for 2 seconds of user CPU time...
// Caught SIGVTALRM
