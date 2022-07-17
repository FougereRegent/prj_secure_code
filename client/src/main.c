#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>


#define ERROR_ADDR_IP -10
#define ERROR_SEND_MSG -20
#define ERROR_RECV_MSG -30
#define LENGHT_ADDR_IP 17
#define LENGHT_FORMAT_DATE

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


int main(int argc, char **argv)
{
    char addr_ip[LENGHT_ADDR_IP];
    char forma_date[]

    if(argc == 3)
    {
        const int size_chaine = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) : LENGHT_ADDR_IP;
        strncpy(addr_ip, argv[1], size_chaine);
        addr_ip[LENGHT_ADDR_IP-1] = '\0';
    }
    else if(argc == 4)
    {
        const int size_chaine = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) : LENGHT_ADDR_IP;
        strncpy(addr_ip, argv[1], size_chaine);
        addr_ip[LENGHT_ADDR_IP - 1] = '\0';
    }
    else
    {

    }
    return 0;

}

int send_message(const char *addr_ip, const char *format)
{
    SOCKET sock  = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr = {
            .sin_family = AF_INET,
            .sin_port = htons(8080)
    };
    char data[30];
    int n = 0;
    char recv_data[30];

    if(inet_pton(AF_INET, addr_ip, &addr.sin_addr) < 0)
    {
        perror("inet_pton(): ");
        return -1;
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

    if(send(sock, data, 30, 0) == - 1)
    {
        perror("send(): ");
    }

    if((n = recv(sock, recv_data, 30, 0)) == -1)
    {
        perror("recv(): ");
    }

    printf("%s\n", recv_data);

    return  0;
}