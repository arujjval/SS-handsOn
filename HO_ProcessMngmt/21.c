#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Child inherits Parent's Open fds

int main() {
    int fd;
    
    fd = open("sample.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if(fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid;
    pid = fork();

    if(pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    } 

    if(pid == 0) {
        write(fd, "Child Process\n", 14);
    }
    else {
        write(fd, "Parent process\n", 15);
    }

    close(fd);
    return 0;
}