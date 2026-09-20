#include <stdio.h>

int main() {
    FILE *fp;
    char line[1024];
    ssize_t n;

    // fopen(file, flag) -> FILE*, using C library
    fp = fopen("./texts/copyFile1.txt", "r");

    if(fp == NULL) {
        perror("Error opening File");
        return 1;
    }

    // fgets(buffer, maxLength to read, file pointer) -> pointer to buffer
    // Reads line by line
    while((fgets(line, sizeof(line), fp)) != NULL) {
        printf("%s", line);
    }  

    fclose(fp);
    
    return 0;
}