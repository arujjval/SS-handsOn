#include <stdio.h>
#include <unistd.h>

// The nice value is an attribute of a process that influences 
// how much scheduling preference it gets compared 
// with other normal processes.
// higher nice value -> less preference and vice versa
// range: -20 (more preference) -> 0 (default) ->  +19 (less pref.)

int main()
{
    printf("PID = %d\n", getpid());

    while (1)
    {
    }

    // "renice 10 -p [PID]": cmd to change nice value to 10.

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt/28$ ./program 
// PID = 27405

// arujjval@arujjval:~/SS/HO_ProcessMngmt/28$ renice 10 -p 27405
// 27405 (process ID) old priority 0, new priority 10