#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // First child: execute ls -l

        close(fd[0]);
        close(STDOUT_FILENO);

        // STDOUT_FILENO gets assigned to our pipe's output end
        if (dup(fd[1]) != STDOUT_FILENO) {
            perror("dup");
            _exit(1);
        }

        close(fd[1]);
        
        // ls automatically provides output to standard output
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");

        // terminates process without usual C library cleanup 
        _exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        // Second child: execute wc

        close(fd[1]);
        close(STDIN_FILENO);

        // STDIN_FILENO gets assigned to our pipe's input end
        if (dup(fd[0]) != STDIN_FILENO) {
            perror("dup");
            _exit(1);
        }

        close(fd[0]);

        // wc automatically take input from standard input
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        _exit(1);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
