#ifndef LX_MAX_HEAP_H
#define LX_MAX_HEAP_H

#include <stdint.h>
#include <stdlib.h>

#define swap_arr_uint64(arr,i,j) \
{\
    uint64_t temp;\
    temp = (arr)[(i)];\
    (arr)[(i)] = (arr)[(j)];\
    (arr)[(j)] = temp;\
}

void max_heapify(uint64_t * arr,size_t index,size_t heap_size )
{
    size_t l,r,largest;

    l = index * 2;
    r = index * 2 +1;
    
    if(l <= heap_size && arr[ l-1 ] > arr[ index -1] ){
        largest = l;    
    }else
        largest = index;
    
    if(r <= heap_size && arr[r -1] > arr[largest -1] )
        largest = r;


    if(largest != index){
        swap_arr_uint64(arr,largest-1,index-1);
        max_heapify(arr,largest,heap_size);
    }
}

void build_max_heap(uint64_t * arr,size_t len)
{
    size_t i;
    
    for(i = len/2; i >0; --i){
       max_heapify(arr,i,len);    
    }
}

static int lx_heap_sort(uint64_t * arr,size_t len)
{
    int j;
    
    build_max_heap(arr,len);

    for(j = len; j > 1; --j){
        swap_arr_uint64(arr,j-1,0);
        max_heapify(arr,1,j-1);
        //printf(" %d:%ld\n",j-1,*arr);
    }
}

#endif
