#include <unistd.h>
#include <fcntl.h>


int main() {
    char buffer[100];
    int fd1, fd2, n;

    fd1 = open("./texts/copyFile1.txt", O_CREAT | O_RDONLY | O_RDWR, 0644);
    fd2 = open("./texts/copyFile2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    //offset of fd1 keeps increasing, moving towards end of bytes (byte stream)
    while((n = read(fd1, buffer, sizeof(buffer))) > 0) {
        write(fd2, buffer, n);
    }

    close(fd1);
    close(fd2);
    
    return 0;
}

// OUTPUT: see "./texts/copyFile1.txt" & "./texts/copyFile1.txt"