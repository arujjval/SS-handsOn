#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    /* Ignore SIGINT */
    // SIG_IGN: ignore the signal
    signal(SIGINT, SIG_IGN);

    printf("SIGINT is ignored. Press Ctrl+C for 5 seconds.\n");
    sleep(5);

    /* Reset SIGINT to its default action */
    // SIG_DFL: special constant to restore signal's default action
    signal(SIGINT, SIG_DFL);

    printf("SIGINT reset to default. Press Ctrl+C now.\n");

    while (1)
        pause();

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// SIGINT is ignored. Press Ctrl+C for 5 seconds.
// ^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^CSIGINT reset to default. Press Ctrl+C now.
// ^C
// arujjval@arujjval:~/SS/HO2_SystemV$ 
