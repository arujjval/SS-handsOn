#include <unistd.h>

int main() {
    char buffer[100];
    int n;

    // STDIN_FILENO : 0, fd for standard input
    n = read(STDIN_FILENO, buffer, sizeof(buffer));

    // STDOUT_FILENO : 1, fd for standard output
    if(n > 0) {
        write(STDOUT_FILENO, buffer, n);
    }

    return 0;
}

// OUTPUT 
// Arujjwal
// Arujjwal
