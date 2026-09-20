#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Once we run this, we can inspect the process's fds
// by using command "ls -l /proc/[pid]/fd"
// fd will keep increasing, but number of files will remain same
// because in each iteration, newer fd's will be generated for same files.

int main() 
{
    int fd[5];
    int i;
    char filename[50];

    while (1) {
        for(int i = 0; i < 5; i++) {

            sprintf(filename, "./texts/file_%d.txt", i);

            fd[i] = open(filename, O_CREAT | O_RDWR, 0644);

            if(fd[i] == -1) {
                perror("open");
                return 1;
            }
            
            printf("Created %s - FD: %d\n", filename, fd[i]);
        }
        printf("PID: %d\n", getpid());

        sleep(5);
    }
}