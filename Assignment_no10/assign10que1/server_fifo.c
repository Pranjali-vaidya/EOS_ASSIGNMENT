// server.c - Server
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1, fd2, ret;
    int num1, num2, sum;
    char buf[32];

    
    mkfifo("/tmp/myfifo1", 0666);
    mkfifo("/tmp/myfifo2", 0666);

   
    fd1 = open("/tmp/myfifo1", O_RDONLY);
    if(fd1 < 0) {
        perror("open() failed for reading");
        _exit(1);
    }

    
    ret = read(fd1, buf, sizeof(buf));
    if(ret < 0) {
        perror("read() failed");
        _exit(1);
    }

   
    sscanf(buf, "%d %d", &num1, &num2);
    printf("Server: Received numbers: %d and %d\n", num1, num2);

    
    sum = num1 + num2;

    
    close(fd1);

    
    fd2 = open("/tmp/myfifo2", O_WRONLY);
    if(fd2 < 0) {
        perror("open() failed for writing");
        _exit(1);
    }

    
    ret = write(fd2, &sum, sizeof(sum));
    if(ret < 0) {
        perror("write() failed");
        _exit(1);
    }

    printf("Server: Sent sum to client: %d\n", sum);

    
    close(fd2);

    return 0;
}

