#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    int fd;

    // O_EXCL -> exclusive creation, fail if file already exists
    // Used normally with O_CREAT -> create if not created
    // SC: open(path, flag, file permissions)
    fd = open("./texts/sample.txt", O_RDWR | O_CREAT | O_EXCL, 0644);
    
    // if file already created
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File Descriptor: %d\n", fd);

    close(fd);

    return 0;
}