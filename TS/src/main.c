#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <regex.h>

int set_time(const char *format_time);
int comp_match(char *command);


int main(int argc, char **argv)
{

    return EXIT_SUCCESS;
}

static int regex_match(char *command)
{
    regex_t regex[2];
    int result[2];
    *result = regcomp(regex, "set", 0);
    *(result + 1) = regcomp(regex + 1, "set [:number:]/[:number:]/[:number:] [:number:]:[:number:]:[:number:]", 0);

    int index_regex = 0, error = 0;
    for(; index_regex < 2; index_regex++)
    {
        if(regexec(regex + index_regex, command, 0, NULL, 0) == 0)
        {
            error = 0;
            break;
        }
        error = -1;
    }

    return error;
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
    return -1;
}