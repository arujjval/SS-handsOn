#define _GNU_SOURCE // F_GETPIPE_SZ
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>

int main()
{
    // struct rlimit {
    //     rlim_t rlim_cur;  #soft limit
    //     rlim_t rlim_max;  #hard limit
    // };
    struct rlimit limit;
    int fd[2];
    int pipe_size;

    // Get maximum number of open file descriptors
    // getrlimit(
    //  which resource limit to check (int), 
    //  pointer to rlimit struct, to store limit info
    // ): system call to retrieve resource limits of current process
    // RLIMIT_NOFILE: resource limit for max no. of fds
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("Maximum open file descriptors:\n");
    printf("Soft limit: ");
    
    // RLIM_INFINITY: constant to show unlimited 
    // (hardware-limits still apply)
    if (limit.rlim_cur == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%llu\n", (unsigned long long)limit.rlim_cur);

    printf("Hard limit: ");

    if (limit.rlim_max == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%llu\n", (unsigned long long)limit.rlim_max);

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Get pipe buffer capacity
    // F_GETPIPE_SZ: command for fcnt to get capacity of a pipe's buffer
    pipe_size = fcntl(fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1) {
        perror("fcntl");
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }

    printf("\nPipe buffer size: %d bytes\n", pipe_size);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Maximum open file descriptors:
// Soft limit: 1048576
// Hard limit: 1048576

// Pipe buffer size: 65536 bytes