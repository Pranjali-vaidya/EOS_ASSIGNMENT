#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>
#define SERV_ADDER "172.18.6.198"
#define SERV_PORT 2809
int main()
{
    int ret,serv_fd, cli_fd;
    socklen_t socklen = sizeof(cli_addr);
    char msg[512];
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.Sin_family = AF_INET;
    serv_addr.Sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_fd, 5);
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    do
    {
        /* code */
    } while {
        read(cli_fd, msg, sizeof(msg));
    }
    
}
