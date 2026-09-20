#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record
{
    int id;
    char name[20];
};

int main()
{
    int fd;
    struct record r;
    struct flock lock;

    fd = open("records.dat", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Read lock on Record 2 */

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(struct record);
    lock.l_len = sizeof(struct record);

    printf("Trying to acquire read lock on Record 2...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired.\n");

    /* Read Record 2 */

    lseek(fd, sizeof(struct record), SEEK_SET);
    read(fd, &r, sizeof(r));

    printf("Record 2: ID = %d, Name = %s\n", r.id, r.name);

    /* Unlock */

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Read lock released.\n");

    close(fd);

    return 0;
}