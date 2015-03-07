#ifndef LX_BUFFER_H
#define LX_BUFFER_H
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

typedef enum lx_buffer_mode_t lx_buffer_mode_t;
enum lx_buffer_mode_t
{
	lx_base,
	lx_base_len,
	lx_ebase_offset,
	lx_ebase_offset_len
};

typedef struct lx_buffer lx_buffer;
struct lx_buffer
{
    char * base;
    
    int offset;
    int len;
    int maxlen;
};

void lx_buffer_init(lx_buffer * buff,char * base, int offset,int len, int maxlen);
lx_buffer * lx_buffer_reset(lx_buffer * buff,char * nval,void *( *hmalloc)(size_t size), void (*hfree)(void *) );

#define lx_buffer_lenp(buff) ( (buff)->base + (buff)->len)
#define lx_buffer_offsetp(buff) ( (buff)->base + (buff)->offset)
#define lx_buffer_maxlenp(buff) ( (buff)->base + (buff)->maxlen)

#define lx_buffer_unscannum(buff) ((buff)->len - (buff)->offset)
#define lx_buffer_freenum(buff) ( (buff)->maxlen - (buff)->len)

#endif
