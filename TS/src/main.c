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
                perror("callocl() : ");
                return EXIT_FAILURE;
        }

        snprintf(date_time_string, size_string_date_time_format, "%s %s", argv[1], argv[2]);
        if(set_time(date_time_string) < 0)
        {
            free(date_time_string);
            printf("Error\n");
            return EXIT_FAILURE;
        }
        free(date_time_string);
    }
    return EXIT_SUCCESS;
}

int check_format_time(const char *format_date)
{
    regex_t regex_check_format_time;

    if(regcomp(&regex_check_format_time, "^([0-1][0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$", REG_EXTENDED) != 0)
    {
        printf("The regular expression doesn't compile\n");
        return -1;
    }

    if(regexec(&regex_check_format_time, format_date, 0, NULL, 0) == 0)
    {
        return 0;
    }
    return -1;
}

int set_time(const char *format_time)
{
    /*
    if(check_format_time(format_time) < 0) {
        printf("Format error, use this format hh:mm:ss\n");
        return -1;
    }
    */
    time_t t = time(NULL);
    struct tm *time;

    if(strptime(format_time, "%d/%m/%Y %H:%M:%S", time) == NULL)
    {
        return -1;
    }

    struct timeval new_time = { mktime(time), 0 };

    if(settimeofday(&new_time, 0) == 0)
    {
        return 0;
    }

    return -1;
}