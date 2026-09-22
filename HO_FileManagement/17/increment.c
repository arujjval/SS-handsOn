#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int ticket;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");

    read(fd, &ticket, sizeof(ticket));

    ticket++;

    printf("New ticket number: %d\n", ticket);

    lseek(fd, 0, SEEK_SET);

    write(fd, &ticket, sizeof(ticket));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_FileManagement/17$ ./a.out 
// Write lock acquired.
// New ticket number: 105