//
// Created by damien on 7/6/22.
//

#ifndef PRJ_TREATMENT_TIME_H
#define PRJ_TREATMENT_TIME_H

#define FLAGS_AMERICAN_DATE 0
#define FLAGS_EU_DATE 1
#define SET_TIME_SUCCESS 0
#define SET_TIME_FAILED 1


extern char* get_time(char *format_time, size_t *size_result);
extern int set_time(char *format_time, char flags);

#endif //PRJ_TREATMENT_TIME_H
