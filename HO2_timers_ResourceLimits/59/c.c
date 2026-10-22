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
    signal(SIGFPE, handler);

    printf("Raising SIGFPE...\n");
    fflush(stdout);

    raise(SIGFPE);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Raising SIGFPE...
// Caught SIGFPE
