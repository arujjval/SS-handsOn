#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Client: socket() → connect()

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // The server IP address must be provided as an argument
    if (argc != 2) {
        printf("Usage: %s <server-ip-address>\n", argv[0]);
        return 1;
    }

    // 1. Create a TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server's IP address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Convert the IP address from text to binary form
    if (inet_pton(AF_INET, argv[1],
                  &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address\n");
        close(sock_fd);
        return 1;
    }

    // 3. Connect to the server
    if (connect(sock_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Send a message to the server
    const char *message = "Hello from the client!";
    if (send(sock_fd, message, strlen(message), 0) == -1) {
        perror("send");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Receive the server's reply
    ssize_t n = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Reply from server: %s\n", buffer);
    } else if (n == 0) {
        printf("Server disconnected.\n");
    } else {
        perror("recv");
    }

    // 6. Close the socket
    close(sock_fd);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV/51$ ./client 172.25.64.214
// Reply from server: Hello from the server!