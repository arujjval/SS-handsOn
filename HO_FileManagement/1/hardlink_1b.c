#include <stdio.h>
#include<unistd.h>

int main() {
    //command: ln original.txt hardlink.txt
    if(link("original.txt", "hardlink.txt") == -1) { //System call
        perror("link");
        return 1;
    }

    printf("Hardlink created successfully\n");
    return 0;
}