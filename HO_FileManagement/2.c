#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    while (1) 
    {
        DIR *dir; //pointer to the directory opened RN
        struct dirent *entry;   //info about directory entry like file or subdir
        char path[100];
        char line[200];
        FILE *file;    //pointer to a open file stream, can be used with file related functions

        dir = opendir("/proc");

        if (dir == NULL) {
            printf("Cannot open /proc\n");
            return 1;
        }

        printf("\n ----- Running Processes ------ \n ");
        
        // reading files and subdirs in a dir successively 
        while ((entry = readdir(dir)) != NULL) 
        {   
            //conditions validates the file as a process file in proc
            if(isdigit(entry->d_name[0]))
            {
                // creating string/path
                sprintf(path, "/proc/%s/status", entry->d_name);

                file = fopen(path, "r");

                if(file != NULL) {
                    printf("\nPID: %s\n", entry->d_name);

                    while(fgets(line, sizeof(line), file)) 
                    {   
                        //Comparing validity of process info by string comparison
                        if (strncmp(line, "Name:", 5) == 0 ||   
                            strncmp(line, "State:", 6) == 0 ||
                            strncmp(line, "PPid:", 5) == 0 ||
                            strncmp(line, "VmRSS:", 6) == 0 ||
                            strncmp(line, "Threads:", 8) == 0)
                        {
                            printf("%s", line);
                        } 
                    }

                    fclose(file);
                }

            }
        }

        closedir(dir);

        sleep(5);
    }

    return 0;
}