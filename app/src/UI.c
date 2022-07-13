#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/unistd.h>
#include <regex.h>
#include <string.h>
#include "UI.h"
#include "treatment_time.h"

/*Flags*/
#define FLAGS_DISPLAY_TIME 1
#define FLAGS_SET_TIME 2

/*Prototype*/
static void treatment_command(char *command);
static int comp_match(char *command);
static int regex_match(char *command);
static void now_time(char *format_string);
static void display_result(char *format_string, u_int8_t FLAGS);

void loop_command()
{
    char command[MAX_SIZE];
    while(strcmp(command, "quit\n") != 0)
    {
        printf("> ");
        if (fgets(command, MAX_SIZE, stdin) ){
            treatment_command(command);
        } else {
            perror("Erreur de la fonction");
            exit(1);
        }
        set_time("17/11/2001 10:10:10");
        fflush(stdin);

    }
}

static void treatment_command(char *command)
{
    if(strcmp(command, "quit\n") == 0)
        exit(1);
    else if(comp_match(command) == 0)
    {
        const int size_format_time = strcmp(command, "time\n") == 0 ? 0 : strlen(command) - 6;
        char *format_time = (char*)calloc(sizeof(char), size_format_time);
        strncpy(format_time, strcmp(command, "time\n") == 0 ? "" : command + 5 , size_format_time);

        now_time(format_time);

        free(format_time);
    }
    else if(regex_match(command) == 0)
    {
        printf("It's good pattern \n");
    }
    else
    {
        printf("Error the command or pattern doesn't exist \n");
    }

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
static int comp_match(char *command)
{
    int all_result[NB_KIND_OF_FORMAT_DATE];

    *(all_result + 0) = strcmp(command, "time DD/MM/YYYY\n");
    *(all_result + 1) = strcmp(command, "time DD/MM/YYYY hh:mm:ss\n");
    *(all_result + 2) = strcmp(command, "time MM/DD/YYYY\n");
    *(all_result + 3) = strcmp(command, "time MM/DD/YYYY hh:mm:ss\n");
    *(all_result + 4) = strcmp(command, "time hh:mm:ss\n");
    *(all_result + 5) = strcmp(command, "time\n");

    int index_regex = 0, error = 0;
    for(; index_regex < NB_KIND_OF_FORMAT_DATE; index_regex++  )
    {
        if(*(all_result + index_regex) == 0)
        {
            error = 0;
            break;
        }
        error = -1;
    }
    return error == 0 ? 0 : -1;
}

static void display_result(char *format_string, u_int8_t FLAGS)
{

}

static void now_time(char *format_string)
{
    size_t size;
    char *result_format = get_time(format_string, &size);
    if(result_format != NULL)
    {
        printf("%s\n", result_format);
        free(result_format);
    }
}