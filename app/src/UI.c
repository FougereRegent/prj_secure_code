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
    printf("%s", command);
    free(command);
}

static int regex_match(char *command)
{
    /*Attribution des regex*/
    regex_t *regex = calloc(sizeof (regex_t), NB_KIND_OF_FORMAT_DATE);
    int all_result = calloc(sizeof(int), NB_KIN_OF_FORMAT_DATE);

    *(all_result + 0) = regcomp(regex, "DD/MM/YYYY", 0);
    *(all_result + 1) = regcomp(regex + 1, "DD/MMM/YYYY hh:mm:ss", 0);
    *(all_result + 2) = regcomp(regex + 2, "MM/DD/YYYY", 0);
    *(all_result + 3) = regcomp(regex + 3, "MM/DD/YYYY hh:mm:ss", 0);
    *(all_result + 4) = regcomp(regex + 4, "hh:mm:ss", 0);

    int error = (*(all_result + 0) |
            *(all_result + 1) |
            *(all_result + 2) |
            *(all_result + 3) |
            *(all_result + 4)) == 0 ? 0 : 1;

    int index_regex;
    for(index_regex = 0; index_regex < NNB_KIND_OF_FORMAT_DATE && error == 0; ++index_regex)
    {

    }

    free(regex);
    free(all_result);

    return error
}