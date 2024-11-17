#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MQ_KEY  0x1234


typedef struct msg {
    long id;            
    int num1;           
    int num2;           
    int sum;            
} msg_t;

int main() {
    int mqid, pid, s, ret;

   
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    
    pid = fork();
    if (pid == 0) {
        
        msg_t m1;
        m1.id = 101;  // Message ID for child to parent
        printf("Child: Enter first number: ");
        scanf("%d", &m1.num1);
        printf("Child: Enter second number: ");
        scanf("%d", &m1.num2);

        // Send the numbers to the parent via the message queue
        ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
        if (ret < 0)
            perror("Child: msgsnd() failed");
        else
            printf("Child: Numbers sent to parent: %d, %d\n", m1.num1, m1.num2);

        // Receive the sum from the parent
        msg_t m2;
        ret = msgrcv(mqid, &m2, sizeof(msg_t) - sizeof(long), 102, 0);
        if (ret < 0) {
            perror("Child: msgrcv() failed");
        } else {
            printf("Child: Received sum from parent: %d\n", m2.sum);
        }

        // Child exits
        _exit(0);
    }
    else {
       
        msg_t m2;
        printf("Parent: Waiting for message from child...\n");

        
        ret = msgrcv(mqid, &m2, sizeof(msg_t) - sizeof(long), 101, 0);
        if (ret < 0) {
            perror("Parent: msgrcv() failed");
        } else {
 printf("Parent: Received numbers from child: %d, %d\n", m2.num1, m2.num2);

            
            m2.sum = m2.num1 + m2.num2;
            printf("Parent: Calculated sum: %d\n", m2.sum);

           
            m2.id = 102;  
            ret = msgsnd(mqid, &m2, sizeof(msg_t) - sizeof(long), 0);
            if (ret < 0) {
                perror("Parent: msgsnd() failed");
            } else {
                printf("Parent: Sum sent back to child: %d\n", m2.sum);
            }
        }

     
        waitpid(pid, &s, 0);

        // Destroy message queue
        msgctl(mqid, IPC_RMID, NULL);
        printf("Parent: Exiting...\n");
    }

    return 0;
}

