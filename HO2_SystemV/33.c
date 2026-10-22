#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // 2 pipes for 2 way comm, since pipe is uni-directional
    int fd1[2]; // parent -> child
    int fd2[2]; // child -> parent
    pid_t pid;
    char bufferC[100];
    char bufferP[100];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if(pid == -1) {
        perror("fork");
        exit(1);
    }

    if(pid == 0) {
        // Child Process

        close(fd1[1]);
        close(fd2[0]);
        char message[] = "Hello Parent!";

        ssize_t n;
        n = read(fd1[0], bufferC, sizeof(bufferC) - 1);

        if (n == -1) {
            perror("Child Read");
            exit(1);
        }

        if (n > 0) {
            bufferC[n] = '\0';
            printf("Child Recieved: %s\n", bufferC);
        }

        close(fd1[0]);

        if (write(fd2[1], message, strlen(message) + 1) == -1) {
            perror("Child Write");
            exit(1);
        }

        close(fd2[1]);
        exit(0);
    }
    else {
        // Parent Process

        close(fd1[0]);
        close(fd2[1]);
        char message[] = "Hello Child!";

        if (write(fd1[1], message, strlen(message) + 1) == -1) {
            perror("Parent Write");
            exit(1);
        }

        close(fd1[1]);

        ssize_t n;
        n = read(fd2[0], bufferP, sizeof(bufferP) - 1);

        if (n == -1) {
            perror("Parent Read");
            exit(1);
        }

        bufferP[n] = '\0';
        printf("Parent Recieved: %s\n", bufferP);

        close(fd2[0]);
        waitpid(pid, NULL, 0);
    }   

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Child Recieved: Hello Child!
// Parent Recieved: Hello Parent!