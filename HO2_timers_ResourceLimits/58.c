#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    // pthread_self(): takes no argument
    // kinda like pid() for threads, to get thread ID
    printf("Thread ID: %lu\n",
           (unsigned long)pthread_self());

    return NULL;
}

int main(void)
{
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {

        // int pthread_create(
        //     pthread_t *thread: new thread's ID is stored here,
        //     const pthread_attr_t *attr: Thread attributes; NULL-> default attr
        //     void *(*start_routine)(void *): function to execute (its pointer is shared),
        //     void *arg: arguments to shared function
        // ): 0 -> success, non-zero: error (shares error number directly)
        // Kind of like fork() for threads
        if (pthread_create(&threads[i], NULL,
                           thread_function, NULL) != 0) {
            printf("Failed to create thread %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        // int pthread_join(
        //      pthread_t thread: thread ID to wait for, 
        //      void **retval: address where thread return value should be stored, NULL: dont need that,
        // ): Kinda like waitpid(). waits for completion of specified thread
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// OUTPUT:
// arujjval@arujjval:~/SS/HO2_SystemV$ ./a.out 
// Thread ID: 139776088864448
// Thread ID: 139776080471744
// Thread ID: 139776072079040
