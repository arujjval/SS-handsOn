#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

volatile sig_atomic_t timer_expired = 0;
// volatile: avoid compiler to cache it or assume it unchanged
// sig_atomic_t: special type int for comm b/w signal handler and program

void handler(int signum)
{
    timer_expired = 1;
}

int main(void)
{
    struct itimerval timer;

    // Set the first expiration: 10 seconds + 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Zero interval means the timer does not repeat
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Handle SIGALRM when the timer expires
    signal(SIGALRM, handler);

    // Start the real-time timer
    // int setitimer(int which: kind of time,
    //      const struct itimerval *new_value: setup details,
    //      struct itimerval *old_value: optional, to store prev settings)
    // : to setup timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_REAL started for 10 seconds and 10 microseconds.\n");
    fflush(stdout);

    // Wait until the timer expires
    while (!timer_expired)
        pause();

    printf("ITIMER_REAL expired! Received SIGALRM.\n");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/53$ ./a.out 
// ITIMER_REAL started for 10 seconds and 10 microseconds.
// ITIMER_REAL expired! Received SIGALRM.
