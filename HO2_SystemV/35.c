#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int p1[2], p2[2];

    /* Create two pipes */
    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        perror("pipe");
        exit(1);
    }

    /* First process: ls -l */
    if (fork() == 0)
    {
        dup2(p1[1], STDOUT_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    /* Second process: grep ^d */
    if (fork() == 0)
    {
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    /* Third process: wc */
    if (fork() == 0)
    {
        dup2(p2[0], STDIN_FILENO);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        _exit(1);
    }

    /* Parent closes all pipe descriptors */
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    /* Wait for all three children */
    for (int i = 0; i < 3; i++)
        wait(NULL);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
//      11      99     583
