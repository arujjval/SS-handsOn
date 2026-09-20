#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket = 100;

    fd = open("ticket.txt",
              O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, &ticket, sizeof(ticket));

    close(fd);

    return 0;
}