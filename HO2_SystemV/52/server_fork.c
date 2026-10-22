#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Automatically reap terminated children on Linux/POSIX systems
    // to signal parent process to ignore when got signal of terminated child,
    // instead of storing its info till exit() status (avoiding zombie processes)
    // SIGCHLD: signal sent to the parent when a child process terminates or changes state.
    // SIG_IGN: Ignore the signal
    signal(SIGCHLD, SIG_IGN);

    printf("Fork server listening on port %d...\n", PORT);

    // Keep accepting clients
    while (1) {
        client_fd = accept(server_fd, NULL, NULL);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // Create a child process for this client
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            close(client_fd);
        }
        else if (pid == 0) {
            // CHILD PROCESS
            close(server_fd);  // Child doesn't accept new clients

            char buffer[1024];
            ssize_t n = recv(client_fd, buffer,
                             sizeof(buffer) - 1, 0);

            if (n > 0) {
                buffer[n] = '\0';

                printf("Child %ld received: %s\n",
                       (long)getpid(), buffer);

                const char *reply = "Hello from fork server!";
                send(client_fd, reply, strlen(reply), 0);
            }

            close(client_fd);
            _exit(EXIT_SUCCESS);
        }
        else {
            // PARENT PROCESS
            close(client_fd);  // Parent doesn't handle this client

            printf("Created child process %ld\n", (long)pid);
        }
    }

    close(server_fd);
    return 0;
}