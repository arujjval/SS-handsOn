#include <stdio.h>
#include <sys/stat.h>

// argc: no. of cmd-line argument count, start from 0
// argv: array of strings
int main(int argc, char *argv[]) {
    struct stat st;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1;
    }

    // macros to check file type using st_mode attr. of struct stat
    // st_mode: integer, represents file type and permissions
    if (S_ISREG(st.st_mode))
        printf("Regular file\n");

    else if (S_ISDIR(st.st_mode))
        printf("Directory\n");

    else if (S_ISLNK(st.st_mode))
        printf("Symbolic link\n");

    else if (S_ISCHR(st.st_mode))
        printf("Character device\n");

    else if (S_ISBLK(st.st_mode))
        printf("Block device\n");

    else if (S_ISFIFO(st.st_mode))
        printf("FIFO (named pipe)\n");

    else if (S_ISSOCK(st.st_mode))
        printf("Socket\n");
    else
        printf("Unknown file type\n");

    return 0;   
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_FileManagement$ ./a.out ./sample.txt
// Regular file