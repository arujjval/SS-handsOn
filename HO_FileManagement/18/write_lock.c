#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

    fd = open("records.dat", O_RDWR | O_CREAT, 0666);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Create three records if file is empty */

    lseek(fd, 0, SEEK_SET);

    r.id = 1;
    strcpy(r.name, "Alice");
    write(fd, &r, sizeof(r));

    r.id = 2;
    strcpy(r.name, "Bob");
    write(fd, &r, sizeof(r));

    r.id = 3;
    strcpy(r.name, "Charlie");
    write(fd, &r, sizeof(r));

    /* Write lock on Record 2 */

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(struct record);
    lock.l_len = sizeof(struct record);

    printf("Trying to acquire write lock on Record 2...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");

    /* Read Record 2 */

    lseek(fd, sizeof(struct record), SEEK_SET);
    read(fd, &r, sizeof(r));

    printf("Before modification: %d %s\n", r.id, r.name);

    /* Modify Record 2 */

    strcpy(r.name, "Modified");

    lseek(fd, sizeof(struct record), SEEK_SET);
    write(fd, &r, sizeof(r));

    printf("Record 2 modified.\n");

    /* Unlock */

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Write lock released.\n");

    close(fd);

    return 0;
}