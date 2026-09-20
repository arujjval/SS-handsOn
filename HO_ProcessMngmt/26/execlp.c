#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Using execlp:\n");

    execlp("ls", "ls", "-Rl", NULL);

    perror("execlp");

    return 1;
}