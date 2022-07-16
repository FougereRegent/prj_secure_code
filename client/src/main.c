#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>


typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


int main(int argc, char **argv)
{
    SOCKET sock  = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr = {
            .sin_family = AF_INET,
            .sin_port = htons(8080)
    };

    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) < 0)
    {
        perror("inet_pton(): ");
    }
    if(sock == -1)
    {
        perror("socket(): ");
        return -1;
    }

    if(connect(sock , (SOCKADDR*) &addr, sizeof(addr)) == -1)
    {
        perror("connect(): ");
        return -1;
    }

    return 0;

}