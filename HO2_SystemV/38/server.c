#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd1, fd2;
    char buffer[100];
    char reply[] = "Hello from Server!";
    ssize_t n;

    // Create the two FIFOs
    if (mkfifo("fifo1", 0666) == -1) {
        struct stat st;
        if (stat("fifo1", &st) == -1 || !S_ISFIFO(st.st_mode)) {
            perror("mkfifo fifo1");
            exit(1);
        }
    }

    if (mkfifo("fifo2", 0666) == -1) {
        struct stat st;
        if (stat("fifo2", &st) == -1 || !S_ISFIFO(st.st_mode)) {
            perror("mkfifo fifo2");
            exit(1);
        }
    }

    // Open fifo1 for reading
    fd1 = open("fifo1", O_RDONLY);
    if (fd1 == -1) {
        perror("open fifo1");
        exit(1);
    }

    // Open fifo2 for writing
    fd2 = open("fifo2", O_WRONLY);
    if (fd2 == -1) {
        perror("open fifo2");
        close(fd1);
        exit(1);
    }

    // Receive message from Client
    n = read(fd1, buffer, sizeof(buffer) - 1);
    if (n == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        exit(1);
    }

    if (n == 0) {
        printf("Client closed the FIFO without sending data.\n");
        close(fd1);
        close(fd2);
        return 0;
    }

    buffer[n] = '\0';
    printf("Server received: %s\n", buffer);

    // Send reply to Client
    if (write(fd2, reply, strlen(reply) + 1) == -1) {
        perror("write");
        close(fd1);
        close(fd2);
        exit(1);
    }

    printf("Server sent: %s\n", reply);

    close(fd1);
    close(fd2);

    return 0;
}