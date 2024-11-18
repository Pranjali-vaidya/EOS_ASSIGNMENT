#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF_SIZE 1024

int main() {
    int server_fifo_fd, client_fifo_fd, ret;
    char buf[MAX_BUF_SIZE], fifo_name[128], file_name[128];
    FILE *input_file;

    
    server_fifo_fd = open("/tmp/myfifo", O_RDONLY);
    if (server_fifo_fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    
    ret = read(server_fifo_fd, buf, MAX_BUF_SIZE);
    if (ret < 0) {
        perror("read() failed");
        close(server_fifo_fd);
        _exit(1);
    }

   
    sscanf(buf, "%s %s", fifo_name, file_name);

    
    input_file = fopen(file_name, "rb");
    if (input_file == NULL) {
        perror("fopen() failed");
        close(server_fifo_fd);
        _exit(1);
    }

    
    client_fifo_fd = open(fifo_name, O_WRONLY);
    if (client_fifo_fd < 0) {
        perror("open() failed to open client FIFO");
        fclose(input_file);
        close(server_fifo_fd);
        _exit(1);
    }

    
    printf("Server: Sending file content...\n");
    while (1) {
        ret = fread(buf, 1, MAX_BUF_SIZE, input_file);
        if (ret > 0) {
            write(client_fifo_fd, buf, ret);
        }

        if (ret < MAX_BUF_SIZE) {
            break; 
        }
    }

    printf("Server: File sent successfully.\n");

    
    fclose(input_file);
    close(server_fifo_fd);
    close(client_fifo_fd);

    return 0;
}

