#define _GNU_SOURCE
#define __USE_XOPEN_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include<sys/capability.h>
#include <string.h>
#include <errno.h>

int set_time(const char *format_time);
int check_format_time(const char* format_time);
void init_cap();


int main(int argc, char **argv)
{
    init_cap();
    if(argc == 3)
    {
        const size_t size_string_date_time_format = strlen(argv[1]) + strlen(argv[2]) + 2;
        char *date_time_string = (char*) calloc(sizeof(char), size_string_date_time_format);

        if(date_time_string == NULL)
        {
                return EXIT_FAILURE;
        }
        argv[1][strlen(argv[1])] = ' ';
        if(set_time(argv[1]) < 0)
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

void init_cap()
{
    cap_t cap = cap_get_proc();
    cap_value_t t = CAP_SYS_TIME;
    if(cap_clear_flag(cap, CAP_PERMITTED) == -1)
    {
        cap_free(cap);
        perror("cap_clear_flag() : ");
        exit(1);
    }
    if(cap_clear_flag(cap, CAP_INHERITABLE) == -1)
    {
        cap_free(cap);
        perror("cap_clear_flag() : ");
        exit(1);
    }
    if(cap_clear_flag(cap, CAP_EFFECTIVE) == -1)
    {
        cap_free(cap);
        perror("cap_clear_flag() : ");
        exit(1);
    }

    if(cap_set_flag(cap, CAP_PERMITTED, 1, &t, CAP_SET) == -1)
    {
        perror("cap_set_flag() : ");
    }
    if(cap_set_flag(cap, CAP_EFFECTIVE, 1, &t, CAP_SET) == -1)
    {
        perror("cap_set_flag() : ");
    }
    if(cap_set_flag(cap, CAP_INHERITABLE, 1, &t, CAP_SET) == -1)
    {
        perror("cap_set_flag() : ");
    }

    if(cap_set_proc(cap) == -1)
    {
        printf("Erreur to set cap\n");
    }
    cap_free(cap);
}