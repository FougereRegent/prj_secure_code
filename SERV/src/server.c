#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "server.h"

/*This function initialize a listen socket*/
extern SOCKET *init_socket(const int listen_port)
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
        perror("socket() : ")
        return  NULL;
    }

    if(bind(listen_sock, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
    {
        perror("bind() : ");
        return NULL;
    }

    if(listen(listen_sock, 5) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }

    return (SOCKET*)&listen_sock;
}

extern void listen(SOCKET *listen_socket)
{
    SOCKET csock;
    SOCKADDR_IN csin = {0};
    int sin_csize = sizeof(csin);

    while(1)
    {
        csock = accept(listen_socket, (SOCKADDR *)&csin, &sin_size);
        if(csock == INVALID_SOCKET)
        {
            perror("accept() : ");
            exit(0);
        }
        else
        {
            printf("Connected\n");
        }
    }
}