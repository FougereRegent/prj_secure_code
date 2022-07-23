#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/capability.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define LENGHT_ADDR_IP 17
#define SIZE_BUFFER_DATA 2

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

static int send_message(const char *addr_ip, const int port, const char *format, const size_t taille_msg);
static char* convert_byte_to_char(const uint8_t* array_bytes, size_t *size);
static void init_cap();



int main(int argc, char **argv)
{
    char addr_ip[LENGHT_ADDR_IP];

    int port = 0;
    init_cap();
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

        snprintf(addr_ip, size_string_addr_ip, "%s", argv[1]);

        for(index = 4; index < argc; index++)
        {
            argv[index - 1][strlen(argv[index - 1])] = ' ';
        }


        addr_ip[LENGHT_ADDR_IP-1] = '\0';

        port = atoi(argv[2]);
        send_message(addr_ip, port, argv[3], size_string_format_date);
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

static int send_message(const char *addr_ip, const int port, const char *format, const size_t taille_msg)
{
    SOCKET sock  = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
    };

    if(inet_pton(AF_INET, addr_ip, &addr.sin_addr) < 0)
    {
        return -1;
    }
    if(sock == -1)
    {
        return -1;
    }

    if(connect(sock , (SOCKADDR*) &addr, sizeof(addr)) == -1)
    {
        return -1;
    }

    uint8_t *test = calloc(sizeof(uint8_t), taille_msg + 1);
    int i;
    for(i = 0; i < taille_msg; i++)
    {
        test[i] = format[i];
    }
    test[taille_msg - 1] = 0xFF;
    test[taille_msg] = 0xFF;

    if(send(sock, test, taille_msg + 1, 0) == - 1)
    {
        return -1;
    }

    size_t size_recv_data = 0;
    uint8_t *data = (uint8_t*) malloc(size_recv_data);
    uint8_t *val_recv;
    int n = 0;

    do
    {
        if((n = recv(sock, data, SIZE_BUFFER_DATA, 0)) == -1)
        {
            free(data);
            exit(1);
        }
        if(val_recv == NULL)
        {
            size_recv_data += n;
            val_recv = (uint8_t*) calloc(1, size_recv_data);
            if(val_recv == NULL)
            {
                return -1;
            }
            while(n > 0)
            {
                val_recv[n - 1] = data[n - 1];
                n--;
            }
        }
        else{
            int index;
            size_recv_data += n;
            val_recv = (uint8_t*) realloc(val_recv, size_recv_data);
            for(index = 0; index < n; index++)
            {
                val_recv[size_recv_data - n + index] = data[index];
            }
        }
    }while(val_recv[size_recv_data - 2] != 0xFF || val_recv[size_recv_data - 1] != 0xFF);

    size_recv_data -= 2;

    char *recv_data = convert_byte_to_char(val_recv, &size_recv_data);

    if(recv_data != NULL)
    {
        printf("%s\n", recv_data);
    }
    free(data);
    free(recv_data);

    return  0;
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

static void init_cap()
{
    cap_t cap = cap_get_proc();
    if(cap_clear_flag(cap, CAP_PERMITTED) == -1)
    {
        cap_free(cap);
    }
    if(cap_clear_flag(cap, CAP_EFFECTIVE) == -1)
    {
        cap_free(cap);
    }
    if(cap_set_proc(cap) == -1)
    {
        printf("The capabilities can't set");
    }
    cap_free(cap);
}