#include <stdio.h>
#include <unistd.h>

// to check: ps -o pid,stat,cmd -p [PID]
// to terminate: kill -STOP [PID]

// State: R+: Running, foreground process group

int main() {
    printf("Process started. PID = %d\n", getpid());

    while(1) {
        
    }

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt/19$ ./a.out 
// Process started. PID = 21858

// arujjval@arujjval:~/SS/HO_ProcessMngmt/19$ ps -o pid,stat,cmd -p 22299
//     PID STAT CMD
//   22299 R+   ./a.out

