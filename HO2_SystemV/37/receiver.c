#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buffer[100];
    ssize_t n;

    printf("Receiver: Waiting for sender...\n");

    // Open FIFO for reading
    // This is blocked till sender opens the FIFO
    fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Receive the message
    n = read(fd, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("read");
        close(fd);
        exit(1);
    }

    if (n == 0) {
        printf("Receiver: No message received.\n");
    } else {
        buffer[n] = '\0';
        printf("Receiver received: %s\n", buffer);
    }

    close(fd);
    return 0;
}