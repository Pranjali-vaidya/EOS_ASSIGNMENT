#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 128

int main() {
    int pipe1[2], pipe2[2];  // pipe1 for child to parent, pipe2 for parent to child
    pid_t pid;
    int num1, num2, sum;
    ssize_t ret;

    
    if (pipe(pipe1) == -1) {
        perror("pipe1 creation failed");
        exit(1);
    }

    
    if (pipe(pipe2) == -1) {
        perror("pipe2 creation failed");
        exit(1);
    }

    
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child Process
        close(pipe1[0]);  // Close unused read end of pipe1
        close(pipe2[1]);  // Close unused write end of pipe2

        
        printf("Child: Enter first number: ");
        scanf("%d", &num1);
        printf("Child: Enter second number: ");
        scanf("%d", &num2);

        // Send the numbers to the parent via pipe1
        ret = write(pipe1[1], &num1, sizeof(num1));
        if (ret == -1) {
            perror("Child: write to pipe1 failed");
            exit(1);
        }
        ret = write(pipe1[1], &num2, sizeof(num2));
        if (ret == -1) {
            perror("Child: write to pipe1 failed");
            exit(1);
        }
        close(pipe1[1]);  // Close write end of pipe1 after sending numbers

        
        ret = read(pipe2[0], &sum, sizeof(sum));
        if (ret == -1) {
            perror("Child: read from pipe2 failed");
            exit(1);
        }

        
        printf("Child: Received sum from parent: %d\n", sum);

        close(pipe2[0]);  // Close read end of pipe2 after receiving sum

        exit(0);
    }
    else {  // Parent Process
        close(pipe1[1]);  // Close unused write end of pipe1
        close(pipe2[0]);  // Close unused read end of pipe2

        // Read the numbers from pipe1
        ret = read(pipe1[0], &num1, sizeof(num1));
        if (ret == -1) {
            perror("Parent: read from pipe1 failed");
            exit(1);
        }
        ret = read(pipe1[0], &num2, sizeof(num2));
        if (ret == -1) {
            perror("Parent: read from pipe1 failed");
            exit(1);
        }
        close(pipe1[0]);  // Close read end of pipe1 after receiving numbers

      
        sum = num1 + num2;
        printf("Parent: Calculated sum: %d\n", sum);

        
        ret = write(pipe2[1], &sum, sizeof(sum));
        if (ret == -1) {
            perror("Parent: write to pipe2 failed");
            exit(1);
        }
        close(pipe2[1]);

        wait(NULL);

        exit(0);
    }

    return 0;
}

