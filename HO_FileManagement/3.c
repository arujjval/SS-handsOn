#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // fd is a number that os gives to a process to identify an open file
    // or resource, reference number. This is only relevant within this
    // current process
    int fd;

    // creat -> SC to create file, 0644 -> octal file permission
    fd = creat("./sample.txt", 0644);

    if(fd == -1) {
        perror("creat");
        return 1;
    }

    printf("File created successfully.\n");
    printf("File Descriptor: %d\n", fd);

    close(fd);

    return 0;
}

// OUTPUT
// File created successfully.
// File Descriptor: 3