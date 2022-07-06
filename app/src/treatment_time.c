#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treatment_time.h"

/*Not implemented*/
extern char* get_time(char* format_time, size_t *size_result)
{
    time_t raw_time;
    struct tm *my_time;

    raw_time = time(NULL);
    my_time = gmtime(&raw_time);

    if(strcmp("DD/MM/YYYY", format_time) == 0)
    {
        *size_result = strlen("DD/MM/YYYY");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d/%02d/%d", my_time->tm_mday,
                (my_time->tm_mon) + 1,
                (my_time->tm_year ) + 1900);
        return result;
    }
    else if(strcmp("DD/MM/YYYY hh:mm:ss", format_time) == 0)
    {
        *size_result = strlen("DD/MM/YYYY hh:mm:ss");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d/%02d/%d %02d:%02d:%02d", my_time->tm_mday,
                (my_time->tm_mon) + 1,
                (my_time->tm_year ) + 1900,
                my_time->tm_hour,
                my_time->tm_min,
                my_time->tm_sec);
        return result;
    }
    else if(strcmp("MM/DD/YYYY", format_time) == 0)
    {
        *size_result = strlen("MM/DD/YYYY");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d/%02d/%d", (my_time->tm_mon) + 1,
                my_time->tm_mday,
                (my_time->tm_year ) + 1900);
        return result;
    }
    else if(strcmp("MM/DD/YYYY hh:mm:ss", format_time) == 0)
    {
        *size_result = strlen("MM/DD/YYYY hh:mm:ss");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d/%02d/%d %02d:%02d:%02d", (my_time->tm_mon) + 1,
                my_time->tm_mday,
                (my_time->tm_year ) + 1900,
                my_time->tm_hour,
                my_time->tm_min,
                my_time->tm_sec);
        return result;
    }
    else if(strcmp("hh:mm:ss", format_time) == 0)
    {
        *size_result = strlen("hh:mm:ss");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d:%02d:%02d", my_time->tm_hour,
                my_time->tm_min,
                my_time->tm_sec);
        return result;
    }
    else if(strcmp("", format_time) == 0)
    {
        *size_result = strlen("hh:mm:ss");
        char *result = (char*)calloc(sizeof(char), *size_result);
        sprintf(result,"%02d:%02d:%02d", my_time->tm_hour,
                my_time->tm_min,
                my_time->tm_sec);
        return result;
    }
    else
        return NULL;
}