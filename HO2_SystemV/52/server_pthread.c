#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

// Function executed by each worker thread
void *handle_client(void *arg)
{
    // Get the client's socket descriptor
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[1024];

    // Receive a message from this client
    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';

        printf("Thread %lu received: %s\n",
               (unsigned long)pthread_self(), buffer);

        // Send a reply to this client
        const char *reply = "Hello from pthread server!";
        if (send(client_fd, reply, strlen(reply), 0) == -1)
            perror("send");
    }

    // Close this client's connection
    close(client_fd);

    return NULL;
}

int main(void)
{
    int server_fd;
    struct sockaddr_in server_addr;

    // Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for client connections
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Pthread server listening on port %d...\n", PORT);

    // Accept clients continuously
    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // Allocate separate storage for this client's descriptor
        // Since threads use shared storage, using this without seperate
        // memory allocation can cause bad behaviour, since that memory
        // can be overwritten by some other thread of same process
        int *arg = malloc(sizeof(int));
        if (arg == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        *arg = client_fd;

        pthread_t tid;

        // Create a worker thread for the client
        int err = pthread_create(&tid, NULL, handle_client, arg);

        if (err != 0) {
            fprintf(stderr, "pthread_create: %s\n",
                    strerror(err));
            close(client_fd);
            free(arg);
            continue;
        }

        // Allow the worker thread to clean up when it finishes
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
