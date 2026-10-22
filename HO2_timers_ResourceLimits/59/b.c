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
    signal(SIGINT, handler);

    printf("Press Ctrl+C to send SIGINT.\n");

    while (1)
        // pause(): system call that makes current process sleep until
        // a signal delivered either runs a handler or terminates the process
        // returns -1 when signal handler finishes, setting errno -> EINTR
        // Avoids busy loop (does not waste CPU cycles)
        pause();

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Press Ctrl+C to send SIGINT.
// ^C
// Caught SIGINT (Ctrl+C)
// ^C
// Caught SIGINT (Ctrl+C)
// ^C
// Caught SIGINT (Ctrl+C)
// ^_^\Quit (core dumped)
