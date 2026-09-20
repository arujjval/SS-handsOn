#include <stdio.h>
#include <unistd.h>

// to check: ps -o pid,stat,cmd -p [PID]
// to terminate: kill -STOP [PID]

// State: S+: Sleeping, foreground process group

int main() {
    printf("Process started. PID = %d\n", getpid());

    while(1) {
        printf("Process is running...\n");
        sleep(1);
    }

    return 0;
}