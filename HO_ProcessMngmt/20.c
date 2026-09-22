#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // parent gets child's pid, child gets 0
    pid = fork();

    if(pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
        printf("Child's Parent PID: %d\n", getppid());
    }
    else {
        // Parent Process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
    }

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ ./a.out 
// Parent process: PID = 23072
// Child PID = 23073
// Child Process: PID = 23073
// Child's Parent PID: 23072