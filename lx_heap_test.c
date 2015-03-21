#ifndef LX_HEAP_TEST_H
#define LX_HEAP_TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lx_max_heap.h"
#include "lx_random.h"

void print_arr(uint64_t * arr,int size)
{
    size_t i;

    for(i = 0; i< size; ++i)
        printf(" %lld",arr[i]);
    printf("\n");
}

//int lx_heap_test(int argc, char *argv[])
int test_main(int argc, char *argv[])
{
    int size = 100;
    uint64_t *arr,maxnum,i;   
    
    if(argc > 1)
        size = atoi(argv[1]);
    arr =(uint64_t *) malloc(size * sizeof(uint64_t));
    if(arr == NULL)
        return EXIT_FAILURE;

    lx_rand_uint64_arr(arr,size);
    if(size < 50)
        print_arr(arr,size);

    lx_heap_sort(arr,size);

    if(size < 50)
        print_arr(arr,size);
    
    if(size > 1)
        for( i = 1;i < size;i++)
            assert(arr[i-1] <= arr[i]);
}

#endif
