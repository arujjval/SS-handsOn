
#include <stdio.h>
#include <sys/resource.h>

// Similar to getrlimit() program we saw earlier

void print_limit(const char *name, int resource, const char *unit)
{
    struct rlimit limit;

    if (getrlimit(resource, &limit) == -1) {
        perror("getrlimit");
        return;
    }

    printf("%-25s Soft: ", name);

    if (limit.rlim_cur == RLIM_INFINITY)
        printf("Unlimited");
    else
        printf("%llu %s",
               (unsigned long long)limit.rlim_cur, unit);

    printf(" | Hard: ");

    if (limit.rlim_max == RLIM_INFINITY)
        printf("Unlimited");
    else
        printf("%llu %s",
               (unsigned long long)limit.rlim_max, unit);

    printf("\n");
}

int main(void)
{
    printf("System Resource Limits\n");
    printf("----------------------\n");

    print_limit("CPU time", RLIMIT_CPU, "seconds");
    print_limit("File size", RLIMIT_FSIZE, "bytes");
    print_limit("Data segment size", RLIMIT_DATA, "bytes");
    print_limit("Stack size", RLIMIT_STACK, "bytes");
    print_limit("Core file size", RLIMIT_CORE, "bytes");
    print_limit("Open file descriptors", RLIMIT_NOFILE, "files");
    print_limit("Address space", RLIMIT_AS, "bytes");

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// System Resource Limits
// ----------------------
// CPU time                  Soft: Unlimited | Hard: Unlimited
// File size                 Soft: Unlimited | Hard: Unlimited
// Data segment size         Soft: Unlimited | Hard: Unlimited
// Stack size                Soft: 8388608 bytes | Hard: Unlimited
// Core file size            Soft: 0 bytes | Hard: Unlimited
// Open file descriptors     Soft: 1048576 files | Hard: 1048576 files
// Address space             Soft: Unlimited | Hard: Unlimited