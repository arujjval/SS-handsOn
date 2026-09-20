#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int flags;

    fd = open("./texts/sample.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // F_GETFL: Get flags
    flags = fcntl(fd, F_GETFL);

    if(flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    // O_ACCMODE: mask to keep only read/write bits
    switch(flags & O_ACCMODE) {
        case O_RDONLY:
            printf("%s\n", "Read Only");
            break;
        
        case O_WRONLY:
            printf("%s\n", "Write Only");
            break;
        
        case O_RDWR:
            printf("%s\n", "Both Read Write");
            break;
    }

    close(fd);
    return 0;
}