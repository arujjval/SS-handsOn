#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    // struct to manage locking config in fcntl
    struct flock lock; 

    fd = open("../texts/sample.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);

    if(fd == -1) {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK; // Write Lock
    lock.l_whence = SEEK_SET; // start counting from beginning of file
    lock.l_start = 0; // starting position of lock relative to l_whence
    lock.l_len = 0; // lock till end (makes no sense ik)

    // F_SETLK: flag for fcntl() for locking mechanism 
    if(fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");
    printf("Press Enter to release the lock..\n");
    getchar();

    lock.l_type = F_UNLCK; // UnLock
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_FileManagement/16$ ./a.out 
// Write lock acquired.
// Press Enter to release the lock..
