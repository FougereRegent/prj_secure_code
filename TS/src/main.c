#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

int set_time(const char *format_time);
int comp_match(char *command);
void init();


int main(int argc, char **argv)
{
    init();
    if(argc == 2)
    {
        const size_t size_string_date_time_format = strlen(argv[1]) + 1;
        char *date_time_string = (char*) calloc(sizeof(char), size_string_date_time_format);

        if(date_time_string == NULL)
        {
                perror("callocl() : ");
                return EXIT_FAILURE;
        }

        strncpy(date_time_string, argv[1], size_string_date_time_format);
    }
    return EXIT_SUCCESS;
}

int set_time(const char *format_time)
{
    struct tm *time = getdate(format_time);
    if(getdate_err == 0)
    {
        struct timeval new_time = { mktime(time), 0 };
        if(settimeofday(&new_time, 0) == 0)
        {
            return 0;
        }
    }
    perror("erreur : ");
    return -1;
}

void init()
{
    putenv("DATEMSK=/etc/NC/template.txt");
}