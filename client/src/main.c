#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/capability.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define LENGHT_ADDR_IP 18
#define SIZE_BUFFER_DATA 16

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

static int send_message(const char *addr_ip, const int port, const char *format, const size_t taille_msg);
static char* convert_byte_to_char(const uint8_t* array_bytes, size_t *size);
static int init_cap();


int main(int argc, char **argv)
{
    char addr_ip[LENGHT_ADDR_IP];

    int port = 0;
    if(init_cap() == -1)
    {
        printf("The capabilities can't set\n");
    }
    if(argc > 3)
    {
        const size_t size_string_addr_ip = strlen(argv[1]) <= LENGHT_ADDR_IP ? strlen(argv[1]) + 1 : LENGHT_ADDR_IP;
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
    test[taille_msg] = 0x00;
    if(send(sock, test, taille_msg + 1, 0) == - 1)
    {
        return -1;
    }

    size_t size_recv_data = 0;
    uint8_t *data = (uint8_t*) calloc(1,size_recv_data);
    int n = 0;

    while (1) {
        if ((n = recv(sock, data + size_recv_data, SIZE_BUFFER_DATA, 0)) < 0) {
            break;
        } else {
            size_recv_data += n;
            data = realloc(data, size_recv_data + SIZE_BUFFER_DATA);
            if (data == NULL) {
                return -1;

            }
        }

        if(data[size_recv_data - 1] == 0x00)
        {
            break;
        }
    }

    char *recv_data = convert_byte_to_char(data, &size_recv_data);

    if(recv_data != NULL)
    {
        fprintf(stdout,"%s\n", recv_data);
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

static int init_cap()
{
    cap_t cap = cap_get_proc();
    if(cap_clear_flag(cap, CAP_PERMITTED) == -1)
    {
        cap_free(cap);
        return -1;
    }
    if(cap_clear_flag(cap, CAP_EFFECTIVE) == -1)
    {
        cap_free(cap);
        return -1;
    }
    if(cap_set_proc(cap) == -1)
    {
        cap_free(cap);
        return -1;
    }
    cap_free(cap);
    return 0;
}