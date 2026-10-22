#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <string.h>

int main()
{
    int fd;
    char buffer[100];
    // collections of fds, is needed to use system()
    fd_set readfds;
    struct timeval timeout;
    int ret;
    ssize_t n;

    // Create FIFO
    if (mkfifo("myfifo", 0666) == -1) {
        struct stat st;
        if (stat("myfifo", &st) == -1 || !S_ISFIFO(st.st_mode)) {
            perror("mkfifo");
            exit(1);
        }
    }

    // Open FIFO for reading without waiting for a writer
    fd = open("myfifo", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Waiting for data in FIFO for 10 seconds...\n");

    // Prepare file descriptor set
    FD_ZERO(&readfds); // Clear the set
    FD_SET(fd, &readfds); // Add fd

    // Set timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Wait for FIFO to become readable
    // Do this again in detail...!!!
    ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
        close(fd);
        exit(1);
    }
    else if (ret == 0) {
        printf("Timeout: No data received within 10 seconds.\n");
    }
    else {
        // FIFO is readable
        n = read(fd, buffer, sizeof(buffer) - 1);

        if (n == -1) {
            perror("read");
        }
        else if (n == 0) {
            printf("FIFO reached end-of-file (no writer currently connected).\n");
        }
        else {
            buffer[n] = '\0';
            printf("Received: %s\n", buffer);
        }
    }

    close(fd);
    return 0;
}