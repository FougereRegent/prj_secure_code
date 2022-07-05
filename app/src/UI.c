#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "UI.h"


void loop_command()
{
    char *command = calloc(sizeof(char), MAX_SIZE);
    if(fgets(command, MAX_SIZE, stdin ) != NULL)
    {

        treatment_command(command);
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