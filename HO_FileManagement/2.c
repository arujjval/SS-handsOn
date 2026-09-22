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


// OUTPUT
//  ----- Running Processes ------ 
 
// PID: 1
// Name:   systemd
// State:  S (sleeping)
// PPid:   0
// VmRSS:     12116 kB
// Threads:        1

// PID: 2
// Name:   init-systemd(Ub
// State:  S (sleeping)
// PPid:   1
// VmRSS:      1792 kB
// Threads:        2

// PID: 6
// Name:   init
// State:  S (sleeping)
// PPid:   2
// VmRSS:      1920 kB
// Threads:        2

// PID: 55
// Name:   systemd-journal
// State:  S (sleeping)
// PPid:   1
// VmRSS:     15020 kB
// Threads:        1

// PID: 102
// Name:   systemd-udevd
// State:  S (sleeping)
// PPid:   1
// VmRSS:      6016 kB
// Threads:        1

// PID: 171
// Name:   systemd-resolve
// State:  S (sleeping)
// PPid:   1
// VmRSS:     12672 kB
// Threads:        1

// PID: 172
// Name:   systemd-timesyn
// State:  S (sleeping)
// PPid:   1
// VmRSS:      7680 kB
// Threads:        2

// PID: 181
// Name:   cron
// State:  S (sleeping)
// PPid:   1
// VmRSS:      2432 kB
// Threads:        1

// PID: 182
// Name:   dbus-daemon
// State:  S (sleeping)
// PPid:   1
// VmRSS:      4864 kB
// Threads:        1

// PID: 186
// Name:   ollama
// State:  S (sleeping)
// PPid:   1
// VmRSS:     30580 kB
// Threads:        11

// PID: 190
// Name:   systemd-logind
// State:  S (sleeping)
// PPid:   1
// VmRSS:      8320 kB
// Threads:        1

// PID: 194
// Name:   agetty
// State:  S (sleeping)
// PPid:   1
// VmRSS:      1920 kB
// Threads:        1

// PID: 202
// Name:   rsyslogd
// State:  S (sleeping)
// PPid:   1
// VmRSS:      5120 kB
// Threads:        4

// PID: 215
// Name:   agetty
// State:  S (sleeping)
// PPid:   1
// VmRSS:      1792 kB
// Threads:        1

// PID: 223
// Name:   unattended-upgr
// State:  S (sleeping)
// PPid:   1
// VmRSS:     22144 kB
// Threads:        2

// PID: 352
// Name:   login
// State:  S (sleeping)
// PPid:   2
// VmRSS:      4224 kB
// Threads:        1

// PID: 401
// Name:   systemd
// State:  S (sleeping)
// PPid:   1
// VmRSS:     11136 kB
// Threads:        1
