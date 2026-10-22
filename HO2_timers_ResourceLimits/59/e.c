#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGALRM using setitimer()\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct itimerval timer = {0};

    signal(SIGALRM, handler);

    timer.it_value.tv_sec = 2; // 2 sec
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // Only once
    timer.it_interval.tv_usec = 0;

    printf("Real-time timer set for 2 seconds...\n");
    fflush(stdout);

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    while (1)
        pause();

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Real-time timer set for 2 seconds...
// Caught SIGALRM using setitimer()