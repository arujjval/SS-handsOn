#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd1, fd2;
    char message[] = "Hello from Client!";
    char buffer[100];
    ssize_t n;

    // Open fifo1 for writing
    fd1 = open("fifo1", O_WRONLY);
    if (fd1 == -1) {
        perror("open fifo1");
        exit(1);
    }

    // Open fifo2 for reading
    fd2 = open("fifo2", O_RDONLY);
    if (fd2 == -1) {
        perror("open fifo2");
        close(fd1);
        exit(1);
    }

    // Send message to Server
    if (write(fd1, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd1);
        close(fd2);
        exit(1);
    }

    printf("Client sent: %s\n", message);

    // Receive reply from Server
    n = read(fd2, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        exit(1);
    }

    if (n == 0) {
        printf("Server closed the FIFO without replying.\n");
    } else {
        buffer[n] = '\0';
        printf("Client received: %s\n", buffer);
    }

    close(fd1);
    close(fd2);

    return 0;
}