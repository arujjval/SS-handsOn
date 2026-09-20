#include <stdio.h>
#include <unistd.h>

int main()
{   
    //command: ln -s original.txt softlink.txt
    if (symlink("original.txt", "softlink.txt") == -1) //system call
    {
        perror("symlink");
        return 1;
    }

    printf("Soft link created successfully.\n");

    return 0;
}