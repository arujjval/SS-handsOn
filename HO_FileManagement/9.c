#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() 
{
    struct stat fileStat;
    int n;

    // stat(file, pointer to the stat struct) -> n (int)
    // n = 0 -> success, n = -1 -> failure
    n = stat("./texts/copyFile1.txt", 
        &fileStat);

    if(n == -1) {
        perror("stat");
        return 1;
    }

    printf("Inode number: %ld\n", fileStat.st_ino);
    printf("Hard links: %ld\n", fileStat.st_nlink);
    printf("UID: %d\n", fileStat.st_uid); //User ID
    printf("GID: %d\n", fileStat.st_gid); // Group ID
    printf("Size: %ld bytes\n", fileStat.st_size); // in bytes
    // file preferred block size for I/O
    printf("Block size: %ld bytes\n", fileStat.st_blksize);
    // 512-byte blocks allocated to file
    printf("Number of blocks: %ld\n", fileStat.st_blocks);
    // st_atime is of time_t type (%ld), is seconds since Unix epoch
    // ctime converts that to human-readable (%s), includes \n
    printf("Last access: %s", ctime(&fileStat.st_atime));
    printf("Last modification: %s", ctime(&fileStat.st_mtime));
    printf("Last change: %s", ctime(&fileStat.st_ctime));

    return 0;
}