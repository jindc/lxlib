#ifndef LX_LIST_H
#define LX_LIST_H
#include <sys/types.h>
#include <string.h>
#include "lx_buffer.h"

typedef struct lx_list_node lx_list_node;
struct lx_list_node
{
    lx_list_node * pre;
    lx_list_node * next;
};

typedef struct lx_kvlist_node lx_kvlist_node;
struct lx_kvlist_node
{
    lx_list_node list;

    lx_buffer  key;
    lx_buffer  value;
};

lx_kvlist_node * kvlist_find(lx_kvlist_node * head,char * key,char * ebase,lx_buffer_mode_t mode);

lx_list_node * list_append(lx_list_node ** head,size_t size,void *(* pmalloc)(size_t size));

lx_kvlist_node * 
kvlist_append(lx_kvlist_node ** phead, char * key, char * value,void *(* pmalloc)(size_t size),void(*pfree)(void *) );

void list_free(lx_list_node ** head);

#endif

