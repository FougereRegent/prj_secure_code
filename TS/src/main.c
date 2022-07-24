#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include<sys/capability.h>
#include <string.h>
#include <errno.h>

static int set_time(const char *format_time);
static int init_cap();


int main(int argc, char **argv)
{
    if(init_cap() == -1)
    {
        printf("The capabilities can't set\n");
    }
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

static int set_time(const char *format_time)
{
    time_t now_time = time(NULL);
    struct tm *time = localtime(&now_time);

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

static int init_cap()
{
    cap_t cap = cap_get_proc();
    cap_value_t t[] = {CAP_SYS_TIME};
    ssize_t size = 1;
    if(cap_clear_flag(cap, CAP_PERMITTED) == -1)
    {
        cap_free(cap);
        return -1;
    }
    if(cap_clear_flag(cap, CAP_INHERITABLE) == -1)
    {
        cap_free(cap);
        return -1;
    }
    if(cap_clear_flag(cap, CAP_EFFECTIVE) == -1)
    {
        cap_free(cap);
        return -1;
    }

    if(cap_set_flag(cap, CAP_PERMITTED, size, t, CAP_SET) == -1)
    {
        cap_free(cap);
        return -1;
    }
    if(cap_set_flag(cap, CAP_EFFECTIVE, size, t, CAP_SET) == -1)
    {
        cap_free(cap);
        return -1;
    }

    if(cap_set_proc(cap) == -1)
    {
        cap_free(cap);
        return -1;
    }
    cap_free(cap);
    return 0;
}