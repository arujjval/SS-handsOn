#include <stdio.h>
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
    signal(SIGSEGV, handler);

    printf("Raising SIGSEGV...\n");
    fflush(stdout);

    raise(SIGSEGV);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/59$ ./a.out 
// Raising SIGSEGV...
// Caught SIGSEGV
