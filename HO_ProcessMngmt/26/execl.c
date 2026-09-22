#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Using execl:\n");

    execl("/bin/ls", "ls", "-Rl", NULL);

    perror("execl");

    return 1;
}

// OUTPUT
// Using execl:
// .:
// total 100
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execl
// -rw-r--r-- 1 arujjval arujjval   163 Sep 20 15:03 execl.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execle
// -rw-r--r-- 1 arujjval arujjval   242 Sep 20 15:03 execle.c
// -rwxr-xr-x 1 arujjval arujjval 16048 Sep 20 15:04 execlp
// -rw-r--r-- 1 arujjval arujjval   161 Sep 20 15:03 execlp.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execv
// -rw-r--r-- 1 arujjval arujjval   221 Sep 20 15:03 execv.c
// -rwxr-xr-x 1 arujjval arujjval 16096 Sep 20 15:04 execvp
// -rw-r--r-- 1 arujjval arujjval   219 Sep 20 15:03 execvp.c