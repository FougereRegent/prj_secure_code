//
// Created by damien on 7/16/22.
//

#ifndef PRJ_SERVER_H
#define PRJ_SERVER_H

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in6 SOCKADDR_IN6;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

extern SOCKET init_socket(const int listen_port);
extern void listen_request(SOCKET *listen_sock);

#endif //PRJ_SERVER_H
