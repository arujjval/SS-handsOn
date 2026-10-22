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

    // Handle SIGVTALRM
    signal(SIGVTALRM, handler);

    // Start the virtual CPU timer
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_VIRTUAL started for 10 seconds of user CPU time.\n");
    fflush(stdout);

    // Consume user CPU time until the timer expires
    while (!timer_expired) {
        // Intentionally busy-waiting for demonstration
    }

    printf("ITIMER_VIRTUAL expired! Received SIGVTALRM.\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/53$ ./a.out 
// ITIMER_VIRTUAL started for 10 seconds of user CPU time.
// ITIMER_VIRTUAL expired! Received SIGVTALRM.