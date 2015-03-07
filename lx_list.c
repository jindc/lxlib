#include "lx_list.h"
#include <stdlib.h>

lx_list_node * list_append(lx_list_node ** head,size_t size,void *(* pmalloc)(size_t size))
{
    lx_list_node * item;
    
    if(pmalloc){
        item = (lx_list_node *)pmalloc(size);
     }else  
        item= (lx_list_node *) malloc(size);

    if(item != NULL){
        memset(item,0,size);

        if(*head == NULL)
            *head = item;    
        else{
           item->next =  *head; 
           (*head)->pre = item;
           *head = item;
        }
    }
    return item;
}

lx_kvlist_node * 
kvlist_find(lx_kvlist_node * head,char * key,char * ebase,lx_buffer_mode_t mode)
{
	lx_kvlist_node * cur;
	
	if(head == NULL)
		return NULL;
	
	cur = head;
	while(cur)
	{
		switch(mode)
		{
		case lx_base:
			if(cur->key.base)
			{ 
				if(strcmp(key,cur->key.base )==0)
					return cur;
			}
			break;
		case lx_base_len:
			if(cur->key.base)
			{ 
				if(strncmp(key,cur->key.base,cur->key.len )==0)
					return cur;
			}
			break;
		
		case lx_ebase_offset:
			if( ebase){
				if(strcmp(key,ebase + cur->key.offset) == 0)
					return cur;
			}
			break;
		case lx_ebase_offset_len:
			if( ebase){
				if(strncmp(key,ebase + cur->key.offset,cur->key.len) == 0)
					return cur;
			}
			break;
		}
		cur =(lx_kvlist_node *) cur->list.next;
	}
	
	return NULL;
}

lx_kvlist_node * 
kvlist_append(lx_kvlist_node ** phead, char * key, char * value,void *(* pmalloc)(size_t size),void(*pfree)(void *) )
{
    char * nkeybuff, * nvalbuff;
    lx_kvlist_node * node;
    size_t klen,vlen;

    if(!key && !value)
        return NULL;

    nkeybuff = nvalbuff = NULL;
    node = NULL;
    klen = strlen(key) + 1;
    vlen = strlen(value) + 1;

    nkeybuff = (char *)pmalloc(klen);
    nvalbuff = (char *)pmalloc(vlen);
    node =(lx_kvlist_node*)list_append((lx_list_node ** )phead,sizeof(lx_kvlist_node),pmalloc);
    if( !nkeybuff || !nvalbuff || !node)
        goto err;

    memcpy(nkeybuff,key,klen);
    memcpy(nvalbuff,value,vlen);
    lx_buffer_init(&node->key,nkeybuff,0,klen,vlen);
    lx_buffer_init(&node->value,nvalbuff,0,klen,vlen);
    
    return node;

err:
    if(!nkeybuff)
        pfree(nkeybuff);
    if( !nvalbuff)
        pfree(nvalbuff);
    return NULL;
    
}

void list_free(lx_list_node ** head)
{
    lx_list_node * next, * cur;
    
    cur = * head;
    while( cur != NULL)
    {
        next = cur ->next;
        free(cur);
        cur = next;
    }
    
    *head = NULL;
}


