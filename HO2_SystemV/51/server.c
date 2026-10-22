#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Server: socket() → bind() → listen()

int main(void)
{
    int server_fd, client_fd;
    // structure holding network addresses
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // 1. Create a TCP socket
    // AF_INET: IPv4 addresses
    // SOCK_STREAM: using TCP, reliable byte-stream protocol
    // 0: options (None)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));  // set all values to 0
    server_addr.sin_family = AF_INET; // address family to use
    // accept connections addressed to any local IPv4 network interfaces
    server_addr.sin_addr.s_addr = INADDR_ANY;  
    // to set up server's port number, here 8080 is chosen
    // htons: converts byte order to netowkr byte (big endian)
    server_addr.sin_port = htons(8080);

    // 3. Bind the socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting on port 8080...\n");

    // 5. Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &client_len);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected!\n");

    // 6. Receive a message from the client
    // recv(socket_fd, buffer, length, flags)
    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Message from client: %s\n", buffer);

        // 7. Send a reply to the client
        const char *reply = "Hello from the server!";

        // send(socket_fd, buffer, length, flags)
        if (send(client_fd, reply, strlen(reply), 0) == -1)
            perror("send");
    } else if (n == 0) {
        printf("Client disconnected.\n");
    } else {
        perror("recv");
    }

    // 8. Close the connected socket and listening socket
    close(client_fd);
    close(server_fd);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/51$ ./server 
// Server waiting on port 8080...
// Client connected!
// Message from client: Hello from the client!