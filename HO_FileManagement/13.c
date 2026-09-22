#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{   
    // fd_set: set of fds that we want select() to watch
    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds); // MACRO to empty the fd set
    FD_SET(STDIN_FILENO, &readfds); // puts STDIN (keyboard) in set

    timeout.tv_sec = 10; // wait for 10 sec
    timeout.tv_usec = 0; // wait for 0 microsecond

    printf("Waiting for input for 10 seconds...\n");

    // select(...) -> -1: Error, 0 -> no input, > 0 -> Input is there
    int ret = select(STDIN_FILENO + 1, // range of fds to watch (0...max + 1)
                     &readfds,  // fds to watch for reading
                     NULL, // fd to watch for writing
                     NULL, // exceptional canditions
                     &timeout); // waiting time

    if (ret == -1) {
        perror("select");
        return 1;
    }

    if (ret == 0) {
        printf("Timeout: No input received within 10 seconds.\n");
    }
    else {
        // select() removes those fds from which it got no input.
        // to check if STDIN_FILENO is still in the fd set.
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available on STDIN.\n");

            char buffer[100];

            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (n > 0) {
                buffer[n] = '\0';
                printf("Input: %s", buffer);
            }
        }
    }

    return 0;
}

// OUTPUT 
// Waiting for input for 10 seconds...
// Arujjwal Negi Mtech CSE
// Data is available on STDIN.
// Input: Arujjwal Negi Mtech CSE