#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <time.h>
#include <sys/time.h>
//#include "UI.h"

void init();

int main(int argc, char **argv)
{
    init();
    loop_command();
    return EXIT_SUCCESS;
}

void init()
{
    putenv("DATEMSK=./template.txt");
}