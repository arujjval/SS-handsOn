#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char buffer[10];

    fd = open("./texts/seekFile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if(fd < 0) {
        perror("Open File");
        return 1;
    }

    if(read(STDIN_FILENO, buffer, 10) > 0) {
        write(fd, buffer, 10);
    }

    // lseek(fd, offset movement to right in bytes, from pos) -> latest offset (off_t)
    // SEEK_CUR: current offset
    // off_t: kind of long int, to rep position (offset) inside a file
    off_t pos;
    // Will create a gap of \0 (NULL) chars
    pos = lseek(fd, 10, SEEK_CUR);


    if(pos == (off_t)-1) {
        perror("lseek");
        return 1;
    }

    if(read(STDIN_FILENO, buffer, 10) > 0) {
        write(fd, buffer, 10);
    }

    // Open file with 'od' command now

    printf("Value of lseek: %ld\n", pos);

    close(fd);

    return 0;
}