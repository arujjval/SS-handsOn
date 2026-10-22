#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

static inline uint64_t read_tsc(void)
{
    unsigned int low, high;

    // Have to understand this ig!!!!
    __asm__ volatile (
        // helps serialize execution so the timestamp read is
        // better ordered relative to surrounding instructions
        "lfence\n\t"   
        "rdtsc"  // reads CPU's time stamp counter
        : "=a"(low), "=d"(high)
        :
        : "memory"  // compiler memory barrier
    );

    return ((uint64_t)high << 32) | low;
}

int main(void)
{
    uint64_t start, end;
    pid_t ppid;
    volatile pid_t result = 0;

    start = read_tsc();

    for (int i = 0; i < 100; i++) {
        ppid = getppid();
        result = ppid;
    }

    end = read_tsc();

    printf("Parent process ID: %d\n", (int)result);
    printf("Total TSC ticks for 100 getppid() calls: %llu\n",
           (unsigned long long)(end - start));
    printf("Average TSC ticks per call: %.2f\n",
           (double)(end - start) / 100.0);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Parent process ID: 41645
// Total TSC ticks for 100 getppid() calls: 142065
// Average TSC ticks per call: 1420.65
