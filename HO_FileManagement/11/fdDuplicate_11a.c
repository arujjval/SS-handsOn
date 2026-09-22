#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd, fd2;

    fd = open("../texts/sample.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if(fd == -1) {
        perror("Open File");
        return 1;
    }

    write(fd, "Hello\n", 6);

    // Simple OS assigned duplicate fd for same file (inode)
    fd2 = dup(fd);
    
    write(fd2, "World\n", 6);

    close(fd);
    close(fd2);
}

// OUTPUT
// Hello
// World
