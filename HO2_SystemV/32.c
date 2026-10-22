#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> // waitpid()

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "This is message from parent to child.";
    char buffer[100];
    ssize_t n;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { 
        // Child Process
        close(fd[1]); // closing child part of write end

        n = read(fd[0], buffer, sizeof(buffer) - 1);

        if(n == -1) {
            perror("Read Error");
            close(fd[0]);
            exit(1);
        }

        if(n > 0) {
            buffer[n] = '\0';
            printf("Child received: %s\n", buffer);
        }

        close(fd[0]);
        exit(0);
    }
    else {
        close(fd[0]); // closing parent part of read end

        if (write(fd[1], message, strlen(message) + 1) == -1) {
            perror("Write error.");
        }

        close(fd[1]);

        //  (pid, &status: int, options) ....more details needed?
        waitpid(pid, NULL, 0); // to avoid child become zombie
    }

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Child received: This is message from parent to child.