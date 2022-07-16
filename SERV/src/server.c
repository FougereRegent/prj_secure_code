#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"


/*This function initialize a listen socket*/
extern SOCKET init_socket(const int listen_port)
{
    /*Initializing of socket*/
    SOCKADDR_IN sin = {
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_family = AF_INET,
            .sin_port = htons(listen_port)
    };

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(listen_sock == -1)
    {
        perror("socket() : ");
        return  -1;
    }

    if(bind(listen_sock, (SOCKADDR *) &sin, sizeof(sin)) == -1)
    {
        perror("bind() : ");
        return -1;
    }

    if(listen(listen_sock, 5) == -1)
    {
        perror("listen()");
        exit(0);
    }

    return listen_sock;
}

extern void listen_request(SOCKET *listen_socket)
{
    SOCKET csock;
    SOCKADDR_IN csin = {0};
    int sin_csize = sizeof(csin);
    char data[30];

    while(1)
    {
        int n = 0;
        csock = accept(*listen_socket, (SOCKADDR *)&csin, &sin_csize);
        if(csock == -1)
        {
            perror("accept() : ");
            exit(0);
        }
        else
        {
            printf("Connected\n");
            send_response(csock);
        }
    }
}

extern void send_response(SOCKET client_socket)
{
    char data[RECV_SIZE_MSG];
    if((n = recv(client_socket, data, RECV_SIZE_MSG, 0)) == -1)
    {
        perror("recv(): ");
        exit(1);
    }



}