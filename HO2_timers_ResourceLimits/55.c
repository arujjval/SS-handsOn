
#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
    struct rlimit limit;

    /* Get the current limit */
    // RLIMIT_NOFILE: Resource limit - Number of Files (max no. of fds)
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("Before setting limit:\n");
    printf("Soft limit = %llu\n",
           (unsigned long long)limit.rlim_cur);
    printf("Hard limit = %llu\n",
           (unsigned long long)limit.rlim_max);

    /* Set the soft limit to 100 */
    limit.rlim_cur = 100;

    /* Apply the new limit */
    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("setrlimit");
        return 1;
    }

    /* Verify the new limit */
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("\nAfter setting limit:\n");
    printf("Soft limit = %llu\n",
           (unsigned long long)limit.rlim_cur);
    printf("Hard limit = %llu\n",
           (unsigned long long)limit.rlim_max);

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Before setting limit:
// Soft limit = 1048576
// Hard limit = 1048576

// After setting limit:
// Soft limit = 100
// Hard limit = 1048576