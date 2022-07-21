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
int check_format_time(const char* format_time);


int main(int argc, char **argv)
{
    if(argc == 3)
    {
        const size_t size_string_date_time_format = strlen(argv[1]) + strlen(argv[2]) + 2;
        char *date_time_string = (char*) calloc(sizeof(char), size_string_date_time_format);

        if(date_time_string == NULL)
        {
                return EXIT_FAILURE;
        }

        snprintf(date_time_string, size_string_date_time_format, "%s %s", argv[1], argv[2]);
        if(set_time(date_time_string) < 0)
        {
            free(date_time_string);
            return EXIT_FAILURE;
        }
        free(date_time_string);
    }
    return EXIT_SUCCESS;
}


int set_time(const char *format_time)
{
    struct tm time;

    if(strptime(format_time, "%d/%m/%Y %H:%M:%S", &time) == NULL)
    {
        return -1;
    }

    struct timeval new_time = { mktime(&time), 0 };

    if(settimeofday(&new_time, 0) == 0)
    {
        return 0;
    }

    return -1;
}