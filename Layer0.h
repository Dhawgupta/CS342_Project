//
// Created by dawg on 4/27/18.
//
/**
 * Header File for Layer 0
 * This will act as an interface which seems as if we are reading and writing onto a secondary storage
 * 1. Allocate Memory : This funciton will be used to allocate memrory
 * 2. There will be two interafces to our secondary memory
 *      2.1 Read(block)
 *      2.2 Write(Block)
 */
#ifndef CS342_PROJECT_LAYER0_H
#define CS342_PROJECT_LAYER0_H

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 4096 // block size as 4KB
#endif

void* allocate_memory_size(int); // allocate memory in terms of Byte size
void* allocate_memory_block(int); // allocate the memory in terms of Block Size
/** Read a Block
     *
     * 1. Read from this starting point of memory
     * 2. The block number to be read
     * 3. Memory to which the block has to be read
     * 4, return type is 0 if success -1 if failure
     */
int read_block(void*,int,void *); // read the specidifed block number to the specifed buffer
/** Write a Block
     *
     * 1. Write from this starting point of memory
     * 2. The block number to be written
     * 3. Memory from which block has to be written
     * 4. Return type is 0 if success and -1 if failure
     */
int write_block(void*, int , void *);


#endif //CS342_PROJECT_LAYER0_H


