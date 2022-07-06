//
// Created by damien on 7/5/22.
//
#ifndef PRJ_UI_H
#define PRJ_UI_H
#define MAX_SIZE 26
#define NB_KIND_OF_FORMAT_DATE 6
extern void loop_command();

static void treatment_command(char *command);
static int regex_match(char *command);
static void now_time(char *format_string);
static void set_time(char *value);
static void display_result(char *format_string, u_int8_t FLAGS);
/*
 There are two kind of command, they are describe below :
    - time -> this request is used to return date in specific format
    - set -> this request is used to set a new date
*/
#endif //PRJ_UI_H
