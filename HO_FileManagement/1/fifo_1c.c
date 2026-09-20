//Does not work in wsl

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    //command: mkfifo myfifo
    if (mkfifo("myfifo", 0666) == -1) //SC
    {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully.\n");

    return 0;
}