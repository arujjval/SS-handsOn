#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Using execl:\n");

    execl("/bin/ls", "ls", "-Rl", NULL);

    perror("execl");

    return 1;
}