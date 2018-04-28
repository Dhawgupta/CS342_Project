//
// Created by dawg on 4/27/18.
//

#include "Layer0.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void* allocate_memory_size(int size_in_bytes){
//    int size = size_in_bytes;
    void *memory = (void*)malloc(size_in_bytes);
    return memory;
}

void* allocate_memory_block(int number_of_blocks){
    void *memory = (void *)malloc(BLOCK_SIZE*number_of_blocks);
    return memory;
}

int read_block(void* memory,int block,void * buf){
    void *block_location = (void *)((char *)memory + block*BLOCK_SIZE);
    void *newbuf = memcpy(buf,block_location,BLOCK_SIZE); // copy one block worth of memory from the destined location
    if(newbuf == buf)
        return 0;
    else
        return -1;

}
int write_block(void* memory, int block, void * buf){
    void *block_location =(void *)((char *)memory + block*BLOCK_SIZE);
    void *newbuf = memcpy(block_location,buf,BLOCK_SIZE); // copy one block worth of memory from the destined location
    if(newbuf == block_location)
        return 0;
    else
        return -1;
}