#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    struct sigaction sa;

    /* Ignore SIGINT */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is ignored for 5 seconds.\n");
    printf("Press Ctrl+C; the program will not terminate.\n");

    sleep(5);

    /* Reset SIGINT to its default action */
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("\nSIGINT reset to default action.\n");
    printf("Press Ctrl+C now to terminate the program.\n");

    while (1)
    {
        pause();
    }

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// SIGINT is ignored for 5 seconds.
// Press Ctrl+C; the program will not terminate.
// ^C^C^C^C^C^C^C^C^C^C
// SIGINT reset to default action.
// Press Ctrl+C now to terminate the program.
// ^C
// arujjval@arujjval:~/SS/HO2_SystemV$ 
