#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    char cmd[512], *ptr, *args[32];
    int i, ret, err, s;

    while (1) {
        printf("cmd> ");
        
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0; 

        
        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;
        i++;
        while (ptr != NULL) {
            ptr = strtok(NULL, " ");
            args[i] = ptr;
            i++;
        }

        
        if (strcmp(args[0], "exit") == 0) {
            _exit(0);
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] != NULL) {
                chdir(args[1]);
            } else {
                printf("cd: missing argument\n");
            }
        } else if (strcmp(args[0], "kill") == 0) {
            
            if (args[1] != NULL && args[2] != NULL) {
                int pid = atoi(args[1]); 
                int signal_num = atoi(args[2]); 

                if (pid <= 0 || signal_num <= 0) {
                    printf("Invalid PID or signal number\n");
                } else {
                    
                    if (kill(pid, signal_num) == -1) {
                        perror("Error sending signal");
                    } else {
                        printf("Signal %d sent to process %d successfully.\n", signal_num, pid);
                    }
                }
            } else {
                printf("Usage: kill <PID> <signal_number>\n");
            }
        } else {
            
            ret = fork();
            if (ret == 0) {
                err = execvp(args[0], args);
                if (err < 0) {
                    perror("exec() failed");
                    _exit(1);
                }
            } else {
                waitpid(-1, &s, 0);
            }
        }
    }
    return 0;
}

