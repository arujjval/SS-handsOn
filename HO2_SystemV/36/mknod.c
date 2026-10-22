#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    // mknod(
    //  file name, 
    //  S_IFIFO: file is FIFO | 0666: permissions (read and write),
    //  device number. For FIFO, should be zero.
    // ) -> 0 on success, -1 on failure
    if (mknod("fifo_mknod", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    printf("FIFO created using mknod() successfully\n");
    return 0;
}