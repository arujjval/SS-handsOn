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