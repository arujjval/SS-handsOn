#include <stdio.h>

// env. variables: name=value type info that current process can use
// environ: variable, used to access all env. variables of current process
// It is pointer to an array of pointers to strings


// extern: variable already exists elsewhere, use that. No new define
// since environ is predefined global variable
extern char **environ;

int main() {
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n",*env);
        env++;
    }

    return 0;
}