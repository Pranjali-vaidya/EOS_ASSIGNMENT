#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>
#define SERV_ADDR "172.18.6.198"
#define SERV_PORT 2809

int main()
{
    int ret,cli_fd;
    struct sockaddr_in serv_addr;
    char msg[512];
    cli_fd = socket(AF_INET, SOCK_STREAM,0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(SERV_ADDR < 0)
    {
        perror("SERV_ADDR() failed");
        _exit(1);
    }
    do
    {
        printf("client: ");
        gets(msg);
        write(cli_fd, msg, strlen(msg)+1);
        read(cli_fd, msg, sizeof(msg));
        printf("server: %s\n", msg);
    }
    while(strcmp(msg, "bye")!=0);
    close(cli_fd);
    return 0;
}
    
    