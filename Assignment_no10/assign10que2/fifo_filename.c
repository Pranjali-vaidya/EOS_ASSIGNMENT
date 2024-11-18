#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_PATH "/tmp/myfifo" 
#define MAX_BUF_SIZE 1024

int main() {
    int fd, ret;
    char fifo_name[128], file_name[128];
    char buf[MAX_BUF_SIZE];

   
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    
    printf("Enter FIFO name (server-side FIFO): ");
    scanf("%s", fifo_name);
    printf("Enter the file name to send: ");
    scanf("%s", file_name);

    
    snprintf(buf, MAX_BUF_SIZE, "%s %s", fifo_name, file_name);
    ret = write(fd, buf, strlen(buf) + 1);
    if (ret < 0) {
        perror("write() failed");
        close(fd);
        _exit(1);
    }

    printf("Client: FIFO name and file name sent\n");

    
    close(fd);

    
    fd = open(fifo_name, O_RDONLY);
    if (fd < 0) {
        perror("open() failed to open client FIFO");
        _exit(1);
    }

    
    int bytes_read = 0;
    FILE *output_file = fopen(file_name, "wb"); 
    if (output_file == NULL) {
        perror("fopen() failed");
        close(fd);
        _exit(1);
    }

    printf("Client: Receiving file...\n");
    while ((bytes_read = read(fd, buf, MAX_BUF_SIZE)) > 0) {
        fwrite(buf, 1, bytes_read, output_file); 
    }

    printf("Client: File received and saved successfully.\n");

  
    fclose(output_file);
    close(fd);

    return 0;
}

