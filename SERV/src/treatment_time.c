#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treatment_time.h"

/*Not implemented*/
extern char* get_time(const char* format_time, size_t *size_result)
{
    time_t raw_time;
    struct tm *my_time;
    size_t result_strftime = 0;
    *size_result = 16;
    char *result = (char*) calloc(sizeof(char), *size_result);
    if (result == NULL)
    {
        return NULL;
    }

    raw_time = time(NULL);
    my_time = localtime(&raw_time);

    while((result_strftime = strftime(result, *size_result, format_time, my_time)) == 0)
    {
        *size_result += 16;
        if((result = realloc(result, *size_result)) == NULL)
        {
            return NULL;
        }
    }

    *size_result = result_strftime + 1;
    if((result = realloc(result, *size_result)) == NULL)
    {
        return NULL;
    }
    return result;
}

extern int set_time(const char *time)
{
    const char *path_of_file = "/bin/NC/ts";
    const size_t size_of_string = strlen(time) + strlen(path_of_file) + 2;
    char *string = (char*)calloc(sizeof(char), size_of_string);

    snprintf(string, size_of_string, "%s %s", path_of_file, time);

    if(!system(string))
    {
        free(string);
        return -1;
    }
    free(string);

    return 0;
}