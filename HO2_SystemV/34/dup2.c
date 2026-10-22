#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;

    if(pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();

    if(pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // Child 1
        
        close(fd[0]);

        if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
            perror("dup2 child 1");
            exit(1);
        }

        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");

        _exit(1);
    }

    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        // Child 2

        close(fd[1]);

        if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
            perror("dup2 Child 2");
            exit(1);
        }

        close(fd[0]);

        execlp("wc", "wc", NULL);
        perror("wc");

        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}