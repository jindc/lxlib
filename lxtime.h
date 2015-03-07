#ifndef LXTIME_H
#define LXTIME_H
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline int getdatetime(time_t t,const char * fmt,char * buff,size_t size)
{
    struct tm dt;
    if(localtime_r(&t,&dt) == NULL)
        return 0;
    return strftime(buff,size,fmt,&dt);  
}

/*yyyy-mm-dd_hh:MM:ss*/
static inline int getwidetime(time_t t, char* buff, size_t size )
{
    const char * fmt = "%Y-%m-%d_%H:%M:%S";
    return getdatetime(t,fmt,buff,size);
}

/*yyyymmdd_hhMM:ss*/
static inline int getnarrowtime(time_t t, char* buff, size_t size )
{
    const char * fmt = "%y%m%d_%H%M%S";
    return getdatetime(t,fmt,buff,size);
}
/*Mon, 02 Feb 2015 07:58:36 GMT*/
static inline int get_browser_time(time_t t, char* buff, size_t size )
{
    const char * fmt = "%a, %d %b %y %H:%M:%S GMT";
    return getdatetime(t,fmt,buff,size);
}


static inline time_t getnexthour(time_t t,int newhour)
{
    struct tm dt;
    time_t ret;
    if(localtime_r(&t,&dt) == NULL)
        return -1;
   
    dt.tm_hour = newhour;
    dt.tm_min = 0;
    dt.tm_sec = 0;
    ret = mktime(&dt);
    if(-1 == ret )
        return -2;
    if(difftime(ret , time(NULL)) <= 0)
        ret += 24*60*60;
    return ret;
}

static  inline void testlxtime()
{
    char buff[1024];
    getwidetime(time(NULL), buff,1024);
    printf("time:[%s]\n ",buff);
    getnarrowtime(time(NULL),buff,1024);
    printf("time:[%s]\n",buff);
}

static inline char * gettimeval(struct timeval *start, struct timeval * end)
{
    long long start_usec,end_usec,inval;
    int day,h,m,s,milli, usecond;
    static char buff[128];

    start_usec= start->tv_sec * 1000*1000 + start->tv_usec;
    end_usec = end->tv_sec * 1000 * 1000 + end->tv_usec;
    inval = end_usec - start_usec;
    
    if(inval < 0)
        *buff = 0;

    usecond = inval %1000;
    inval /=1000;

    milli = inval % 1000;
    inval /=1000;

    s = inval % 60;
    inval /=60;

    m = inval % 60;
    inval /=60;

    h = inval %24;
    day =  inval/24;
    
    snprintf(buff,128,"%d day,%d hour,%d min,%d second,%d milli,%d usec"
            , day,h,m,s,milli,usecond);
    return buff;
}

static long get_inval_micros(struct timeval * start,struct timeval * end)
{
    struct timeval temp;
    if(!end){
        gettimeofday(&temp,NULL);
        end = &temp;
    }

    return (long)(end->tv_sec * 1000000 + end->tv_usec - start->tv_sec * 1000000 - start->tv_usec); 
}

static long get_micros()
{   
    struct timeval temp;
    gettimeofday(&temp,NULL);
    return (long)(temp.tv_sec * 1000000 + temp.tv_usec);
}

#endif
