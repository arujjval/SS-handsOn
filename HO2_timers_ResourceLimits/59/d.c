#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGALRM using alarm()\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    signal(SIGALRM, handler);

    printf("Alarm set for 5 seconds...\n");
    fflush(stdout);

    alarm(5);

    while (1)
        pause();

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Alarm set for 5 seconds...
// Caught SIGALRM using alarm()
