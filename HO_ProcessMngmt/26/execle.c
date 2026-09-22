#include <stdio.h>
#include <unistd.h>

int main()
{
    char *env[] = {
        "PATH=/bin:/usr/bin",
        NULL
    };

    printf("Using execle:\n");

    execle("/bin/ls", "ls", "-Rl", NULL, env);

    perror("execle");

    return 1;
}

// OUTPUT
// Using execle:
// .:
// total 100
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execl
// -rw-r--r-- 1 arujjval arujjval   815 Sep 22 17:00 execl.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execle
// -rw-r--r-- 1 arujjval arujjval   244 Sep 22 17:00 execle.c
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execlp
// -rw-r--r-- 1 arujjval arujjval   161 Sep 20 15:03 execlp.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execv
// -rw-r--r-- 1 arujjval arujjval   221 Sep 20 15:03 execv.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execvp
// -rw-r--r-- 1 arujjval arujjval   219 Sep 20 15:03 execvp.c