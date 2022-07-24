#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"
#include "treatment_time.h"

#define SIZE_BUFFER_DATA 16
/*Prototypes*/
static int send_result_request(const SOCKET* client_socket,const char *message, const size_t size_msg);
static void *send_response(void *client_socket);
static char* convert_byte_to_char(const uint8_t* array_bytes, size_t *size);


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
        return  -1;
    }

    if(bind(listen_sock, (SOCKADDR *) &sin, sizeof(sin)) == -1)
    {
        return -1;
    }

    if(listen(listen_sock, 5) == -1)
    {
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
            exit(0);
        }
        else
        {
            pthread_t thread;
            if(pthread_create(&thread, NULL, &send_response, (void*)&csock) < 0)
            {
                exit(1);
            }
        }
    }
}

static void *send_response(void *client_socket) {
    size_t size_data = 0;
    uint8_t *data = (uint8_t *) calloc(1, SIZE_BUFFER_DATA);

    SOCKET csock = *((SOCKET *) client_socket);

    int n = 0;

    if (data == NULL) {
        exit(1);
    }

    while (1) {
        if ((n = recv(csock, data + size_data, SIZE_BUFFER_DATA, 0)) < 0) {
            break;
        } else {
            size_data += n;
            data = realloc(data, size_data + SIZE_BUFFER_DATA);
            if (data == NULL) {
                return NULL;

            }
        }

        if(data[size_data - 1] == 0x00)
        {
            break;
        }
    }

        char *format_date = convert_byte_to_char(data, &size_data);

        if (format_date == NULL)
            return NULL;

        char *result = get_time(format_date, &size_data);

        send_result_request(&csock, result, size_data);

        free(format_date);
        free(data);
        return NULL;
}


int send_result_request(const SOCKET* client_socket,const char *message, const size_t size_msg)
{
    uint8_t *byte_message = calloc(sizeof(uint8_t), size_msg);
    int i;
    for(i = 0; i < size_msg; i++)
    {
        byte_message[i] = message[i];
    }
    byte_message[size_msg - 1] = 0x00;
    if(send(*client_socket, byte_message, size_msg, 0) == -1)
    {
        return -1;
    }
    return 0;
}

static char* convert_byte_to_char(const uint8_t* array_bytes, size_t *size)
{
    char *string = (char*)calloc(sizeof(size_t), *size);
    if(string == NULL)
    {
        return NULL;
    }

    size_t index;
    for(index = 0; index < *size; index++)
    {
        char c = (char)array_bytes[index];
        if(c >= 0 && c <= 127)
        {
            string[index] = (char)array_bytes[index];
        }
        else
        {
            return NULL;
        }
    }
    if(string[*size - 1] != '\0')
    {
        *size += 1;
        string = realloc(string, *size);
        if(string == NULL)
        {
            return NULL;
        }
        string[*size - 1] = '\0';
    }
    return string;
}