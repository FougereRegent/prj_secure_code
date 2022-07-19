#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define LENGHT_ADDR_IP 17
#define RECV_SIZE_MESSAGE 8

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

int send_message(const char *addr_ip, const int port, const char *format, const size_t taille_msg);


int main(int argc, char **argv)
{
    char addr_ip[LENGHT_ADDR_IP];

    int port = 0;

    if(argc > 3)
    {
        const size_t size_string_addr_ip = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) : LENGHT_ADDR_IP;
        size_t size_string_format_date = 0;
        int index;

        for(index = 3; index < argc; index++)
        {
            size_string_format_date += strlen(argv[index]);
        }
        size_string_format_date += argc - 3;

        char *format_date = (char*)calloc(sizeof(char), size_string_format_date);
        if(format_date == NULL)
        {
            perror("calloc() : ");
            return -1;
        }

        strncpy(addr_ip, argv[1], size_string_addr_ip);
        for(index = 3; index < argc; index++)
        {
            strncat(format_date, argv[index], strlen(argv[index]));
            strncat(format_date, " ", 1);
        }

        format_date[size_string_format_date -1 ] = '\0';

        addr_ip[LENGHT_ADDR_IP-1] = '\0';

        port = atoi(argv[2]);
        send_message(addr_ip, port, format_date, size_string_format_date);
        free(format_date);

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

    return EXIT_SUCCESS;
}

int send_message(const char *addr_ip, const int port, const char *format, const size_t taille_msg)
{
    SOCKET sock  = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
    };

    size_t size_recv_data = RECV_SIZE_MESSAGE;
    char *recv_data = (char*)calloc(sizeof(char), RECV_SIZE_MESSAGE);
    int n = 0;

    if(recv_data == NULL)
    {
        perror("calloc() : ");
        return -1;
    }

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

    if(send(sock, format, taille_msg, 0) == - 1)
    {
        perror("send(): ");
        return -1;
    }
    do
    {
        if((n = recv(sock, recv_data + (size_recv_data - RECV_SIZE_MESSAGE), RECV_SIZE_MESSAGE, 0)) == -1)
        {
            perror("recv(): ");
            free(recv_data);
            return -1;
        }
        size_recv_data += n;
        recv_data = (char*)realloc(recv_data, size_recv_data);

    } while(n == RECV_SIZE_MESSAGE);

    printf("%s\n", recv_data);
    free(recv_data);
    return  0;
}