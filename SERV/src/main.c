#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include "UI.h"
#include "server.h"

int main(int argc, char **argv)
{
    SOCKET sock = init_socket(8080);
    listen_request(&sock);
    return EXIT_SUCCESS;
}