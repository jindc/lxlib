#include "lx_buffer.h"

void lx_buffer_init(lx_buffer * buff,char * base, int offset,int len, int maxlen)
{
    buff->base = base;
    buff->offset = offset;
    buff->len = len;
    buff->maxlen = maxlen;
}

lx_buffer * lx_buffer_reset(lx_buffer * buff,char * nval,void *( *hmalloc)(size_t size), void (*hfree)(void *) )
{
    char * newb;
    size_t len;

    len = strlen(nval);
    newb = (char *)hmalloc(len+1);
    if(!newb)
        return NULL;
    memcpy(newb,nval,len);
    newb[len] = 0;

    if(buff->base)
        hfree(buff->base);

    lx_buffer_init(buff,newb,0,len,len);
    return buff;
}


