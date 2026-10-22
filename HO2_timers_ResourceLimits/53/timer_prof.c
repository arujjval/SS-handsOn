#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

volatile sig_atomic_t timer_expired = 0;

void handler(int signum)
{
    timer_expired = 1;
}

int main(void)
{
    struct itimerval timer;

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Handle SIGPROF
    signal(SIGPROF, handler);

    // Start the profiling CPU timer
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_PROF started for 10 seconds of CPU time.\n");
    fflush(stdout);

    // Consume CPU time (user + System) until the timer expires
    while (!timer_expired) {
        // Intentionally busy-waiting for demonstration
    }

    printf("ITIMER_PROF expired! Received SIGPROF.\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/53$ ./a.out 
// ITIMER_PROF started for 10 seconds of CPU time.
// ITIMER_PROF expired! Received SIGPROF.
