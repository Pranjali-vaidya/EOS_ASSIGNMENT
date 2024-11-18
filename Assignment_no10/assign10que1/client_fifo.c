// client.c - Client
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1, fd2, ret;
    int num1, num2, sum;
    char buf[32];

    
    fd1 = open("/tmp/myfifo1", O_WRONLY);
    if(fd1 < 0) {
        perror("open() failed for writing");
        _exit(1);
    }

   
    printf("Client: Enter first number: ");
    scanf("%d", &num1);
    printf("Client: Enter second number: ");
    scanf("%d", &num2);

    
    snprintf(buf, sizeof(buf), "%d %d", num1, num2);
    ret = write(fd1, buf, strlen(buf) + 1);
    printf("Client: Sent numbers: %d and %d\n", num1, num2);

    
    close(fd1);

    
    fd2 = open("/tmp/myfifo2", O_RDONLY);
    if(fd2 < 0) {
        perror("open() failed for reading");
        _exit(1);
    }

    
    ret = read(fd2, &sum, sizeof(sum));
    if(ret < 0) {
        perror("read() failed");
        _exit(1);
    }

    
    printf("Client: Received sum from server: %d\n", sum);

    
    close(fd2);

    return 0;
}

