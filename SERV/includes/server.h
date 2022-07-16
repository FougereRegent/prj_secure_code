//
// Created by damien on 7/16/22.
//

#ifndef PRJ_SERVER_H
#define PRJ_SERVER_H

#define RECV_SIZE_MSG 30
#define ERROR_SOCKET -1
#define ERROR_RECV -1
#define ERROR_SEND -1
#define ERROR_BIND -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

extern SOCKET init_socket(const int listen_port);
extern void listen_request(SOCKET *listen_sock);
extern void send_response(SOCKET client_socket);
#endif //PRJ_SERVER_H
