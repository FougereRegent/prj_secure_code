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
    char *date_time_string;

    init();
    switch (argc)
    {
        case 2:
            date_time_string = (char*) calloc(sizeof(char), strlen(argv[0]) + 1);
            strcpy(date_time_string, argv[1]);
            if(set_time(date_time_string) == -1)
            {
                if(date_time_string == NULL)
                    free(date_time_string);
                return EXIT_FAILURE;
            }
            break;
        case 3:
            date_time_string = (char*) calloc(sizeof(char), strlen(argv[0]) + strlen(argv[1]) + 2);
            strcpy(date_time_string, argv[1]);
            strcat(date_time_string, " ");
            strcat(date_time_string, argv[2]);
            if(set_time(date_time_string) == -1)
            {
                if(date_time_string == NULL)
                    free(date_time_string);
                return EXIT_FAILURE;
            }
            break;
        default:
            break;
    }

    if(date_time_string == NULL)
        free(date_time_string);
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