#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    pid_t pid;

    /* Step 1: Create child process */
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        /* Parent exits */
        return 0;
    }

    /* Step 2: Create a new session */
    if (setsid() < 0)
    {
        return 1;
    }

    sleep(5);
    printf("This is a deamon process\n");

    /* Step 3: Open log file */
    int log = open("mydaemon.log",
                   O_WRONLY | O_CREAT | O_APPEND,
                   0644);

    if (log == -1)
    {
        return 1;
    }

    /* Step 4: Close standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Step 5: Write immediately */
    char message[] = "Daemon started successfully!\n";

    write(log, message, sizeof(message) - 1);

    close(log);

    return 0;
}

// OUTPUT
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ ./a.out 
// arujjval@arujjval:~/SS/HO_ProcessMngmt$ This is a deamon process


