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
#define LENGHT_FORMAT_DATE 21

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


int main(int argc, char **argv)
{
    char addr_ip[LENGHT_ADDR_IP];
    char format_date[LENGHT_FORMAT_DATE];
    int port = 0;

    if(argc == 4)
    {
        const size_t size_string_addr_ip = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) : LENGHT_ADDR_IP;
        const size_t size_string_format_date = strlen(argv[3]) <= LENGHT_FORMAT_DATE ? strlen(argv[3]) : LENGHT_FORMAT_DATE;

        strncpy(addr_ip, argv[1], size_string_addr_ip);
        strncpy(format_date, argv[3], size_string_format_date);

        addr_ip[LENGHT_ADDR_IP-1] = '\0';
        format_date[LENGHT_FORMAT_DATE-1] = '\0';

        port = atoi(argv[2]);


    }
    else if(argc == 5)
    {
        const size_t size_string_addr_ip = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) : LENGHT_ADDR_IP;

        strncpy(addr_ip, argv[1],size_string_addr_ip );
        strncpy(format_date, argv[3], 10);
        strncat(format_date, " ", 1);
        strncat(format_date, argv[4], 9);
        addr_ip[LENGHT_ADDR_IP - 1] = '\0';

        port = atoi(argv[2]);

        printf("%s\n", format_date);
    }
    else
    {
        printf("There missed some args\n");
        printf("client addr_ipv4 port format_date\n");
        return EXIT_FAILURE;
    }

    if(port <= 0)
    {
        printf("The port must be greater than 0\n");
        return EXIT_FAILURE;
    }

    switch(send_message(addr_ip, port, format_date)){
        case 0:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }

    return EXIT_SUCCESS;
}

int send_message(const char *addr_ip, const int port, const char *format)
{
    SOCKET sock  = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
    };

    char data[30];
    char recv_data[30];
    int n = 0;

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
        return -1;
    }

    if((n = recv(sock, recv_data, 30, 0)) == -1)
    {
        perror("recv(): ");
        return -1;
    }
    recv_data[n] = '\0';
    printf("%s\n", recv_data);

    return  0;
}