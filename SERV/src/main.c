#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <sys/capability.h>
#include "UI.h"
#include "server.h"
#include "treatment_time.h"

void init_cap();

int main(int argc, char **argv)
{
    pthread_t thread_server;

    init_cap();
    SOCKET sock = init_socket(8080);

    pthread_create(&thread_server, NULL, &listen_request, (void*)&sock);
    loop_command();
    return EXIT_SUCCESS;
}

void init_cap()
{
    cap_t cap = cap_get_proc();
    if(cap_clear_flag(cap, CAP_PERMITTED) == -1)
    {
        cap_free(cap);
        exit(1);
    }
    if(cap_clear_flag(cap, CAP_EFFECTIVE) == -1)
    {
        cap_free(cap);
        exit(1);
    }
    if(cap_set_proc(cap) == -1)
    {
        printf("The capabilities can't set");
        exit(1);
    }
    cap_free(cap);
}