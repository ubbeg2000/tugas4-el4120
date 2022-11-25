#include "date.h"
#include <stdio.h>
#include <time.h>

void get_time(char *time_str)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(time_str, "Current local time and date: %s", asctime(timeinfo));
}