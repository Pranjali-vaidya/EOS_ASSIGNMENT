#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_PORT   2809        
#define BACKLOG      5          

int main() {
    int ret, serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    int num1, num2, sum;

    
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_fd < 0) {
        perror("Server socket creation failed");
        return 1;
    }

    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("Bind failed");
        close(serv_fd);
        return 1;
    }

    
    ret = listen(serv_fd, BACKLOG);
    if (ret < 0) {
        perror("Listen failed");
        close(serv_fd);
        return 1;
    }

    printf("Server: Listening on port %d...\n", SERV_PORT);

   
    cli_len = sizeof(cli_addr);
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &cli_len);
    if (cli_fd < 0) {
        perror("Accept failed");
        close(serv_fd);
        return 1;
    }

    printf("Server: Accepted connection from client\n");

    
    read(cli_fd, &num1, sizeof(num1));
    read(cli_fd, &num2, sizeof(num2));

    
    sum = num1 + num2;

    
    write(cli_fd, &sum, sizeof(sum));

    printf("Server: The sum of %d and %d is %d\n", num1, num2, sum);

    
    close(cli_fd);
    close(serv_fd);
    return 0;
}

