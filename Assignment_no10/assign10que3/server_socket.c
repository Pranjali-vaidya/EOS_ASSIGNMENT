#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/socket_example" 

int main() {
    int ret, serv_fd, cli_fd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t cli_len;
    int num1, num2, result;

    
    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serv_fd < 0) {
        perror("Server socket creation failed");
        return 1;
    }

    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);

    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("Server socket bind failed");
        close(serv_fd);
        return 1;
    }

    
    ret = listen(serv_fd, 5);
    if (ret < 0) {
        perror("Server listen failed");
        close(serv_fd);
        return 1;
    }

    printf("Server is listening for incoming connections...\n");

    
    cli_len = sizeof(cli_addr);
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &cli_len);
    if (cli_fd < 0) {
        perror("Server accept failed");
        close(serv_fd);
        return 1;
    }

    
    read(cli_fd, &num1, sizeof(num1));
    read(cli_fd, &num2, sizeof(num2));

    
    result = num1 + num2;

    
    write(cli_fd, &result, sizeof(result));

    printf("Server: Sent the sum %d to the client\n", result);

    
    close(cli_fd);
    close(serv_fd);

    
    unlink(SOCKET_PATH);

    return 0;
}

