/*!
 * Copyright (c) airfox 2011
 *
 * \file time.c
 * \brief time utility
 *
 * \author airfox <airgis@163.com>
 */

#if defined(UNIX) || defined(LINUX)
#include <sys/time.h>
#elif defined(WIN32)
#include <windows.h>
#endif

#include "time.h"
#include <time.h>
#include <assert.h>

double time_get_now(TimeInfo *cur_time)
{
    time_t t = time(NULL);
    struct tm *loc_time = localtime(&t);

    assert(cur_time != NULL);
    cur_time->year = loc_time->tm_year + 1900;
    cur_time->month = loc_time->tm_mon + 1;
    cur_time->day = loc_time->tm_mday;
    cur_time->hour = loc_time->tm_hour;
    cur_time->minute = loc_time->tm_min;
    cur_time->second = loc_time->tm_sec;
    cur_time->weekday = loc_time->tm_wday;

    return (double)t;
}

double time_get_timestamp()
{
    time_t stamp = time(NULL);
    return (double)stamp;
}

void time_get_microsecond(TimeMicro *micro_time)
{
#if defined(UNIX) || defined(LINUX)
    struct timeval time;
    gettimeofday(&time, NULL);

    assert(micro_time != NULL);
    micro_time->second = (int)(time.tv_sec);
    micro_time->microsecond = (int)(time.tv_usec);
#elif defined(WIN32)
    LARGE_INTEGER li;
    double sec_per_tick;
    double second;
    int microsecond;

    QueryPerformanceFrequency(&li);
    sec_per_tick = 1.0 / li.QuadPart;

    QueryPerformanceCounter(&li);
    second = sec_per_tick * li.QuadPart;
    microsecond = (second - (int)second) * 1000000;

    assert(micro_time != NULL);
    micro_time->second = (int)(second);
    micro_time->microsecond = microsecond;
#endif
    return;
}

int time_get_delay(TimeMicro *start_time, TimeMicro *end_time, TimeMicro *sub_time)
{
    /*Exception*/
    assert(start_time != NULL && end_time != NULL && sub_time != NULL);
    if(start_time->second > end_time->second)
    {
        return -1;
    }
    if(start_time->second == end_time->second && 
            start_time->microsecond > end_time->microsecond)
    {
        return -1;
    }

    sub_time->second = end_time->second - start_time->second;
    sub_time->microsecond = end_time->microsecond - start_time->microsecond;
    if(sub_time->microsecond < 0)
    {
        sub_time->second--;
        sub_time->microsecond += 1000000;
    }

    return 0;
}
