#include <stdio.h> // printf(), perror()
#include <unistd.h> // pipe(), write(), read()
#include <string.h> // strlen() 
#include <stdlib.h> // exit()

int main() {
    int fd[2]; // fd[0]: read end, fd[1]: write end
    char write_msg[] = "Hello! This is a pipe comm.";
    char read_msg[100];

    if (pipe(fd) == -1) {
        // perror: reads errno. errno indicated reason of failure
        perror("Pipe creation failed");
        exit(1);
    }

    //                                      includes \0 
    write(fd[1], write_msg, strlen(write_msg) + 1);

    read(fd[0], read_msg, sizeof(read_msg));

    printf("Message received: %s\n", read_msg);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Message received: Hello! This is a pipe comm.