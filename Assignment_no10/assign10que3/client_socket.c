#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/socket_example" 

int main() {
    int ret, cli_fd;
    struct sockaddr_un serv_addr;
    int num1, num2, result;

    
    cli_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cli_fd < 0) {
        perror("Client socket creation failed");
        return 1;
    }

    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);

    
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("Client connection failed");
        close(cli_fd);
        return 1;
    }

    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    
    write(cli_fd, &num1, sizeof(num1));
    write(cli_fd, &num2, sizeof(num2));

   
    read(cli_fd, &result, sizeof(result));
    printf("Server: The sum is %d\n", result);

   
    close(cli_fd);
    return 0;
}

