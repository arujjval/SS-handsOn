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