#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> // struct stat
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[] = "Hello from sender!";

    // Create the FIFO
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");

        // FIFO may already exist; verify it before continuing
        
        // struct stat st: store info about a file (type, size, permissions)
        struct stat st;
        // stat(): saves files info in st
        // st.st_mode: file type and permission info. 
        // S_ISFIFO: macro to check if file is a FIFO
        if (stat("myfifo", &st) == -1 || !S_ISFIFO(st.st_mode))
            exit(1);
    }

    printf("Sender: Waiting for receiver...\n");

    // Open FIFO for writing
    // This is blocked till receiver opens the FIFO
    // Can be changed by using O_NONBLOCK flag
    fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Send the message
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }

    printf("Sender: Message sent.\n");

    close(fd);
    return 0;
}
