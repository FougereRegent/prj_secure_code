#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"
#include "treatment_time.h"

/*Prototypes*/
static int send_result_request(const SOCKET* client_socket,const char *message, const size_t size_msg);
static void send_response(SOCKET client_socket);
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

extern void *listen_request(void *listen_socket)
{
    SOCKET *listen_sock = (SOCKET*) listen_socket;
    SOCKET csock;
    SOCKADDR_IN csin = {0};
    socklen_t sin_csize = sizeof(csin);

    while(1)
    {
        csock = accept(*listen_sock, (SOCKADDR *)&csin, &sin_csize);
        if(csock == -1)
        {
            perror("accept() : ");
            exit(0);
        }
        else
        {
            pthread_t thread;
            pthread_create(&thread, NULL, &send_response, (void*)&csock);
        }
    }
}

static void *send_response(SOCKET client_socket)
{
    size_t size_data = RECV_SIZE_MSG;
    char *data = calloc(sizeof(char), RECV_SIZE_MSG);
    if(data == NULL)
    {
        perror("calloc() : ");
        exit(1);
    }
    int n = 0;

    do
    {
        if((n = recv(client_socket, data + (size_data - RECV_SIZE_MSG), RECV_SIZE_MSG, 0)) == -1)
        {
            perror("recv() : ");
            exit(1);
        }
        size_data += n;
        data = (char*)realloc(data, size_data);
        if(data == NULL)
        {
            perror("realloc() : ");
            exit(1);
        }
    }while(n == RECV_SIZE_MSG);

    size_t size_result;
    char *result = get_time(data, &size_result);

    if(result == NULL)
    {
        send_result_request(&client_socket, error_msg, strlen(error_msg));
    }
    send_result_request(&client_socket, result, size_result );

}

int send_result_request(const SOCKET* client_socket,const char *message, const size_t size_msg)
{
    if(send(*client_socket, message, size_msg, 0) == -1)
    {
        return ERROR_SEND;
    }
    return SUCCESS_SEND;
}