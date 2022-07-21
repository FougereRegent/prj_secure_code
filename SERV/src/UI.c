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
#define FLAG_DISPLAY_TIME 1
#define FLAG_SET_TIME 2
#define FLAG_QUIT_APP 3

/*Prototype*/
static int treatment_command(const char *command);
static int regex_match(const char *command, const int flag);
static void now_time(char *format_string);
static void clear_stdin();

void loop_command()
{
    char command[MAX_SIZE_COMMAND_INPUT];
    int result_treatment_command = -1;
    do
    {
        printf("> ");
        if (fgets(command, MAX_SIZE_COMMAND_INPUT, stdin) ){
            if(!strchr(command, '\n'))
            {
                clear_stdin();
            }
            result_treatment_command = treatment_command(command);
        } else {
            result_treatment_command = -1;
        }
    }while(!result_treatment_command);
}

static int treatment_command(const char *command)
{
    if(regex_match(command, FLAG_QUIT_APP) == 0)
    {
        return -1;
    }
    else if(regex_match(command, FLAG_DISPLAY_TIME) == 0)
    {
        const int size_format_time = strcmp(command, "time\n") == 0 ? 6 : strlen(command) - 4;
        char *format_time = (char*)calloc(sizeof(char), size_format_time);
        if(format_time == NULL)
        {
            return -1;
        }
        snprintf(format_time, size_format_time, "%s", strcmp(command, "time\n") == 0 ? "%D %T" : command + 4);
        now_time(format_time);

        free(format_time);
        return 0;
    }
    else if(regex_match(command, FLAG_SET_TIME) == 0)
    {
        const int size_string = strlen(command) - 4;
        char *new_time = (char*)calloc(sizeof(char), strlen(command) - 4);

        if(new_time == NULL)
        {
            return -1;
        }
        snprintf(new_time, size_string, command + 4,"%s",  size_string);

        set_time(new_time);
        free(new_time);
        return 0;
    }
    else
    {
        printf("Error the command or pattern doesn't exist \n");
        return 0;
    }

}

static int regex_match(const char *command, const int flag) {
    regex_t regex;
    int result = 0;

    switch (flag) {
        case FLAG_DISPLAY_TIME:
            result = regcomp(&regex, "^time\n", 0);
            break;
        case FLAG_SET_TIME:
            result = regcomp(&regex, "^set ([0-1][0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])\n?$", REG_EXTENDED);
            break;
        case FLAG_QUIT_APP:
            result = regcomp(&regex, "^quit\n?$", REG_EXTENDED);
            break;
    }
    if (regexec(&regex, command, 0, NULL, 0) == 0 && result == 0)
        return 0;

    return -1;
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

static void clear_stdin()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF){};
}