#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{   
    // mkfifo( File name, permissions) -> 0 on success
    if (mkfifo("fifo_mkfifo", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("FIFO created using mkfifo() successfully\n");
    return 0;
}