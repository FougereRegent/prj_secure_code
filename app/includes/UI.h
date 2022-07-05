//
// Created by damien on 7/5/22.
//
#ifndef PRJ_UI_H
#define PRJ_UI_H
#define MAX_SIZE 24
#define NB_KIND_OF_FORMAT_DATE 10
extern void loop_command();

static void treatment_command(char *command);
static int regex_match(char *command);
/*
 There are two kind of command, they are describe below :
    - time -> this request is used to return date in specific format
    - set -> this request is used to set a new date
*/
#endif //PRJ_UI_H
