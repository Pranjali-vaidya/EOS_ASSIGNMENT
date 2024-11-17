#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    pid_t pid;
    int status;

  
    for (i = 1; i <= 5; i++) {
        pid = fork();  

        if (pid == -1) {
            
            perror("Fork failed");
            return 1;
        }
        
        if (pid == 0) { 
            for (int j = 1; j <= 5; j++) {
                printf("Child %d (PID %d): %d\n", i, getpid(), j);
                sleep(1); 
            }
            _exit(0); 
        }
        else {
            
        }
    }

   
    for (i = 1; i <= 5; i++) {
        waitpid(-1, &status, 0);
    }

    printf("Parent: All child processes have completed.\n");

    return 0;
}

