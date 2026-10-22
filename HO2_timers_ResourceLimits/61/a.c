#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    const char msg[] = "Caught SIGSEGV\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void)
{
    // stores signal-handling config
    struct sigaction sa;

    // specifies the handler function to run
    sa.sa_handler = handler;

    // sa_sa_mask: additional signals (set) to be temporarily blocked while handler executes
    // sigemptyset(): initialize signal set to empty 
    // Blocked means will be delivered later
    // sigaddset(set, signal): to add a signal to the set
    sigemptyset(&sa.sa_mask);

    // default flags
    sa.sa_flags = 0;

    // int sigaction(
    //        int signum: signal to handle,
    //        const struct sigaction *act: pointer to new signal-handling config,
    //        struct sigaction *oldact: to store prev config; NULL: not needed
    // );
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Raising SIGSEGV...\n");
    fflush(stdout);

    raise(SIGSEGV);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/61$ ./a.out 
// Raising SIGSEGV...
// Caught SIGSEGV
