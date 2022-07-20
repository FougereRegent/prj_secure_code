#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <sys/capability.h>
#include "UI.h"
#include "server.h"
#include "treatment_time.h"

int main(int argc, char **argv)
{
    pthread_t thread_server;
    SOCKET sock = init_socket(8080);

    pthread_create(&thread_server, NULL, &listen_request, (void*)&sock);
    loop_command();
    return EXIT_SUCCESS;
}