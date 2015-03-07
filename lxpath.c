#include <string.h>
#include <assert.h>
#include <stdio.h>

int getdir( const char * fname, char * buff, size_t size)
{
    if( fname == NULL || buff == NULL || size <3)
        return -1;
    char * dirend = NULL;  
    if( (dirend = strrchr(fname,'/' )) ||( dirend = strrchr(fname,'\\') ))
    {
        snprintf(buff,size,"%s",fname);
        int end = dirend - fname +1 > (int)size -1 ?(int)size-1: dirend-fname+1;
        buff[end] = 0;
    }else
        snprintf(buff,size,"./");
    return 0;
}

int getfname( const char * fname, char * buff, size_t size)
{
    //separate directory and file name
     char * dirend = NULL;  
    if((dirend = strrchr(fname,'/' )) || (dirend = strrchr(fname,'\\')) )
        dirend +=1; 
    else
        dirend = (char *)fname; 
    snprintf(buff,size,"%s",dirend);
    
    if(strlen(buff) == 0)
        return -1;

    return 0;
}

void testfname()
{
    char buff[1024];
    char * s1 = "aa";
    char * s2 = "bb/cc/aa";
    char * s3 = "bb/cc/";

    getdir(s1,buff,1024);
    assert(0 == strcmp(buff,"./"));
    getdir(s2,buff,1024);
    assert(0 == strcmp(buff,"bb/cc/"));
    
    getdir(s3,buff,1024);
    assert(0 == strcmp(buff,"bb/cc/"));

    int ret = getfname(s1,buff,1024);
    assert(!ret && 0== strcmp("aa",buff));

    ret = getfname(s2,buff,1024);
    assert(!ret && 0 == strcmp("aa",buff) );

    ret = getfname(s3,buff,1024);
    assert(ret);
}

