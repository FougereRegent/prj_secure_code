#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/unistd.h>
#include <regex.h>

#include "UI.h"


void loop_command()
{
    char *command = calloc(sizeof(char), MAX_SIZE);
    printf("> ");
    if(fgets(command, MAX_SIZE, stdin ) != NULL)
    {
        treatment_command(command);
        fflush(stdin);
    }
    else
    {
        perror("Erreur de la fonction");
        exit(1);
    }
}

static void treatment_command(char *command)
{
    if(regex_match(command) == 0)
    {
        printf("It's good\n");
    }
    else
    {
        printf("Erreur");
    }
    free(command);
}

static int regex_match(char *command)
{
    /*Attribution des regex*/
    regex_t *regex = calloc(sizeof (regex_t), NB_KIND_OF_FORMAT_DATE);
    int *all_result = calloc(sizeof(int), NB_KIND_OF_FORMAT_DATE);

    *(all_result + 0) = regcomp(regex, "time DD/MM/YYYY", 0);
    *(all_result + 1) = regcomp(regex + 1, "time DD/MMM/YYYY hh:mm:ss", 0);
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

    free(regex);
    free(all_result);

    return error == 0 ? 0 : 1;
}