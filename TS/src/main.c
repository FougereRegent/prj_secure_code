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
        if(set_time(date_time_string) < -1)
        {
            free(date_time_string);
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
        printf("The regualr expression doesn't compile\n");
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
    if(check_format_time(format_time) < 0) {
        printf("Format error, use this format hh:mm:ss\n");
        return -1;
    }

    const char hours[2] = {format_time[0], format_time[1]};
    const char minutes[2] = {format_time[3], format_time[4]};
    const char seconds[2] = {format_time[6], format_time[7]};

    time_t raw_time = time(NULL);
    struct tm *time  = localtime(&raw_time);

    time->tm_hour = atoi(hours);
    time->tm_min = atoi(minutes);
    time->tm_sec = atoi(seconds);

    struct timeval new_time = { mktime(time), 0 };

    if(settimeofday(&new_time, 0) == 0)
    {
        return 0;
    }

    return -1;
}