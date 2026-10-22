#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <receiver_PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);

    if (kill(pid, SIGSTOP) == -1)
    {
        perror("kill");
        return 1;
    }

    printf("SIGSTOP sent to process %d\n", (int)pid);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/64$ ./sender 118364
// SIGSTOP sent to process 118364