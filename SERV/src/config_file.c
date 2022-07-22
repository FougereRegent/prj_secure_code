#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "config_file.h"
/*Prototypes*/
static int check_format(const char *source, const size_t size);
static size_t nb_character_file(FILE *file);

extern int port_config_file()
{
    FILE *file = fopen("/etc/NC/config.ini", "r");
    if(file == NULL)
    {
        return -1;
    }

}

static int check_format(const char* source, const size_t size)
{
    return -1;
}

static size_t nb_character_file(FILE *file)
{
    size_t size_file = 0;
    char c;
    do
    {
        c = fgetc(file);
        size_file++;
    }while(c != EOF);

    fseek(file, 0, SEEK_SET);
    return size_file;
}