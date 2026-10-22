#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGFPE\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Raising SIGFPE...\n");
    fflush(stdout);

    raise(SIGFPE);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/61$ ./a.out 
// Raising SIGFPE...
// Caught SIGFPE
