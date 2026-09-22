#include <stdio.h>
#include <unistd.h>
#include <sched.h>

// Run program using sudo, needs privileges

int main()
{
    int policy;
    struct sched_param param;

    // Get current scheduling policy, 0: current process
    policy = sched_getscheduler(0); 

    if (policy == SCHED_OTHER) // Normal process
        printf("Current policy: SCHED_OTHER\n");
    else if (policy == SCHED_FIFO) // real-time FIFO
        printf("Current policy: SCHED_FIFO\n");
    else if (policy == SCHED_RR) // real-time round robin
        printf("Current policy: SCHED_RR\n");

    // Set new scheduling policy
    param.sched_priority = 10;

    // current program '0' policy set to real-time FIFO, with priority 10
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Policy changed to SCHED_FIFO\n");

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ sudo ./a.out 
// [sudo] password for arujjval: 
// Current policy: SCHED_OTHER
// Policy changed to SCHED_FIFO