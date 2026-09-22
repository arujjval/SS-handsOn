#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec\n");

    // execl(exe file to execute (path), 
    //       cmd commands ...., 
    //       NULL (end of cmd))
    execl("./hello", "./hello", "Arujjwal", NULL);

    // This won't run, since this same process is now
    // executing ./hello (replaced by ./hello)
    printf("After exec\n");

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt/25$ ./a.out 
// Before exec
// Hello Arujjwal