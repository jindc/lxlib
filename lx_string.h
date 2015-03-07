#ifndef LX_STRING_H
#define LX_STRING_H

#define LX_ACSII_SPACE 0x20
//\n
#define LX_ACSII_NL 0x0A
//\r
#define LX_ACSII_CR 0x0D

#define lx_null2str( str ) ((str)?(str):"")

static char * read2nl(char * buff,int maxlen)
{
    int i;

    if(maxlen <2)
        return NULL;

    for(i = 1; i < maxlen; i++)
    {
        if(buff[i]  == LX_ACSII_NL 
            && buff[i-1] == LX_ACSII_CR)
            return buff + i -1;
    } 

    return NULL;
}

static char * read2str(char * buff, int maxlen, char * str)
{
    int i;
    int matchlen;

    matchlen = strlen(str);
    if(maxlen < matchlen)
        return NULL;

    for(i = 0; i < maxlen - (matchlen -1); i++)
    {
        if( strncmp(buff + i, str,matchlen) == 0  )
            return buff + i;
    } 

    return NULL;
}


static char * read2space(char * buff, int len)
{
    int i;

    for(i = 0; i < len; i++)
    {
        if( buff[i] == LX_ACSII_SPACE)
            return buff + i;
    }
    return NULL;
}

static int match_str(char * buff, char ** arr,int arrlen)
{
    int i ;
    for(i = 0; i < arrlen; ++i)
        if(arr[i] && (strncmp(buff, arr[i], strlen(arr[i])) == 0 ))
            return i;
    return -1;
}

static char * find_by_int(char ** array,int key)
{
    while(*array){
        if(atoi(*array) == key)
            return *(array+1);
        array+= 2;
    }   
    return NULL;
}


#endif
