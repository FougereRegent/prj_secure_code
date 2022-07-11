#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include "UI.h"

void init();

int main(int argc, char **argv)
{
    init();
    loop_command();
    return EXIT_SUCCESS;
}

void init()
{
    cap_value_t val = CAP_SYS_TIME;
    printf("%d\n", CAP_SYS_TIME);
    putenv("DATEMSK=./template.txt");
}