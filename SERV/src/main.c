#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <sys/capability.h>
#include "UI.h"
#include "server.h"
#include "treatment_time.h"

#define DEFAULT_PORT 8080

static void init_cap();
static int port_config_file();

int main(int argc, char **argv)
{
    pthread_t thread_server;

    init_cap();
    SOCKET sock = init_socket(DEFAULT_PORT);

    pthread_create(&thread_server, NULL, &listen_request, (void*)&sock);
    loop_command();
    return EXIT_SUCCESS;
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