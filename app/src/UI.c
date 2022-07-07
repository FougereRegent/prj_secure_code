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
        fflush(stdin);

    }
}

static void treatment_command(char *command)
{
    if(strcmp(command, "quit\n") == 0)
        exit(1);
    else if(regex_match(command) == 0)
    {
        const int size_format_time = strcmp(command, "time\n") == 0 ? 0 : strlen(command) - 6;
        char *format_time = (char*)calloc(sizeof(char), size_format_time);
        strncpy(format_time, strcmp(command, "time\n") == 0 ? "" : command + 5 , size_format_time);

        now_time(format_time);

        free(format_time);
    }
    else
    {
        printf("Error the command or pattern doesn't exist \n");
    }

}

static int regex_match(char *command)
{
    /*Attribution des regex*/
    regex_t regex[NB_KIND_OF_FORMAT_DATE];
    int all_result[NB_KIND_OF_FORMAT_DATE];

    *(all_result + 0) = regcomp(regex, "time DD/MM/YYYY", 0);
    *(all_result + 1) = regcomp(regex + 1, "time DD/MM/YYYY hh:mm:ss", 0);
    *(all_result + 2) = regcomp(regex + 2, "time MM/DD/YYYY", 0);
    *(all_result + 3) = regcomp(regex + 3, "time MM/DD/YYYY hh:mm:ss", 0);
    *(all_result + 4) = regcomp(regex + 4, "time hh:mm:ss", 0);
    *(all_result + 5) = regcomp(regex+5, "time", 0);

    int index_regex = 0, error = 0;
    for(; index_regex < NB_KIND_OF_FORMAT_DATE; index_regex++  )
    {
        if(regexec((regex + index_regex), command, 0, NULL, 0) == 0)
        {
            error = 0;
            break;
        }
        error = 1;
    }
    return error == 0 ? 0 : 1;
}

static void display_result(char *format_string, u_int8_t FLAGS)
{

}

static void now_time(char *format_string)
{
    size_t size;
    char *result_format = get_time(format_string, &size);
    printf("%s\n", result_format);
    free(result_format);
}