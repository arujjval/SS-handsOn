#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    const char msg[] = "\nCaught SIGINT (Ctrl+C)\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to send SIGINT.\n");

    while (1)
        pause();

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/61$ ./a.out 
// Press Ctrl+C to send SIGINT.
// ^C
// Caught SIGINT (Ctrl+C)
// ^C
// Caught SIGINT (Ctrl+C)
// ^\Quit (core dumped)
