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
static void *send_response(void *client_socket);
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
    SOCKADDR_IN csin = {0};
    socklen_t sin_csize = sizeof(csin);

    while(1)
    {
        SOCKET csock = accept(*listen_sock, (SOCKADDR *)&csin, &sin_csize);
        if(csock == -1)
        {
            perror("accept() : ");
            exit(0);
        }
        else
        {
            pthread_t thread;
            if(pthread_create(&thread, NULL, &send_response, (void*)&csock) < 0)
            {
                perror("pthread_vreate() : ");
                exit(1);
            }
        }
    }
}

static void *send_response(void *client_socket)
{
    size_t size_data;
    const char *error_msg_get_time = "get_time() : Format Error";
    SOCKET csock = *((SOCKET*)client_socket);

    int n = 0;
    if((n = recv(csock, &size_data, sizeof(size_t), 0)) == -1)
    {
        perror("recv() : ");
        exit(1);
    }

    char *data = calloc(sizeof(char), size_data);
    if(data == NULL)
    {
        perror("calloc() : ");
        exit(1);
    }

    n = 0;
    if((n = recv(csock, data, size_data, 0)) == -1)
    {
        perror("recv() : ");
        exit(1);
    }

    if(n != size_data)
    {
        printf("The data value is incorrect");
        return;
    }
    else
    {
        size_t size_result;
        char *result = get_time(data, &size_result);
        printf("%d\n", result[size_result - 1]);
        if(result == NULL)
        {
            send_result_request(&csock, error_msg_get_time, sizeof(error_msg_get_time));
        }
        send_result_request(&csock, result, size_result );
    }
    free(data);
}

int send_result_request(const SOCKET* client_socket,const char *message, const size_t size_msg)
{
    if(send(*client_socket, &size_msg, sizeof(size_msg), 0) == -1)
    {
        perror("send() : ");
        return -1;
    }
    if(send(*client_socket, message, size_msg, 0) == -1)
    {
        perror("send() : ");
        return -1;
    }
    return 0;
}