#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGPROF\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer = {0};
    volatile unsigned long counter = 0;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 2;

    printf("Profiling timer set for 2 seconds of CPU time...\n");
    fflush(stdout);

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    while (1)
        counter++;

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Profiling timer set for 2 seconds of CPU time...
// Caught SIGPROF
