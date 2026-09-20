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