
#include <stdio.h>
#include <unistd.h>  // sysconf()
#include <limits.h>
#include <sys/resource.h>

int main(void)
{
    long value;
    struct rlimit limit;

    // sysconf(int name: setting we wanna know): long int
    // asks system for a config value or limit, to get system config info
    // getrlimit() is for a process

    /* a. Maximum length of arguments to exec */
    value = sysconf(_SC_ARG_MAX);
    printf("a. Maximum argument length for exec: %ld bytes\n", value);

    /* b. Maximum simultaneous processes per user ID */
#ifdef _SC_CHILD_MAX
    value = sysconf(_SC_CHILD_MAX);
    printf("b. Maximum simultaneous processes per user ID: %ld\n",
           value);
#else
    printf("b. Process limit per user: not available\n");
#endif

    /* c. Number of clock ticks per second */
    value = sysconf(_SC_CLK_TCK);
    printf("c. Clock ticks per second: %ld\n", value);

    /* d. Maximum number of open files */
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("d. Soft limit on open files: ");
        if (limit.rlim_cur == RLIM_INFINITY)
            printf("Unlimited\n");
        else
            printf("%llu\n",
                   (unsigned long long)limit.rlim_cur);
    } else {
        perror("getrlimit");
    }

    /* e. Size of a page */
    value = sysconf(_SC_PAGESIZE);
    printf("e. Page size: %ld bytes\n", value);

    /* f. Total number of physical pages */
    value = sysconf(_SC_PHYS_PAGES);
    printf("f. Total physical pages: %ld\n", value);

    /* g. Number of currently available physical pages */
    value = sysconf(_SC_AVPHYS_PAGES);
    printf("g. Available physical pages: %ld\n", value);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// a. Maximum argument length for exec: 2097152 bytes
// b. Maximum simultaneous processes per user ID: 30093
// c. Clock ticks per second: 100
// d. Soft limit on open files: 1048576
// e. Page size: 4096 bytes
// f. Total physical pages: 1928499
// g. Available physical pages: 861361