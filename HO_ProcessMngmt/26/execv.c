#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {
        "ls",
        "-Rl",
        NULL
    };

    printf("Using execv:\n");

    execv("/bin/ls", args);

    perror("execv");

    return 1;
}

// OUTPUT
// Using execv:
// .:
// total 100
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execl
// -rw-r--r-- 1 arujjval arujjval   815 Sep 22 17:00 execl.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execle
// -rw-r--r-- 1 arujjval arujjval   895 Sep 22 17:00 execle.c
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execlp
// -rw-r--r-- 1 arujjval arujjval   814 Sep 22 17:00 execlp.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execv
// -rw-r--r-- 1 arujjval arujjval   223 Sep 22 17:00 execv.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execvp
// -rw-r--r-- 1 arujjval arujjval   219 Sep 20 15:03 execvp.c