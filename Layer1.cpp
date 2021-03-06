//
// Created by dawg on 4/27/18.
//

//
// Created by dawg on 4/27/18.
//
// strucutre largely inspired from  : http://pages.cs.wisc.edu/~remzi/OSTEP/file-implementation.pdf
//#include <iostream>
#include "Layer0.h"
#include "Layer1.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
using namespace std;

superblock superblock::read_superblock_fs(void * memory_location){
    void *temp_block = malloc(BLOCK_SIZE);
    read_block(memory_location, 0, temp_block);
    superblock *sp = (superblock*)malloc(sizeof(superblock));
    memcpy(sp, temp_block,sizeof(superblock));
    return *sp;
}
void superblock::write_superblock_fs(void *memory_location, superblock sBlock) {
    void *temp_block = malloc(BLOCK_SIZE);
    // writing the current sBlock to temp blcok
    memcpy(temp_block,&sBlock,sizeof(superblock));
    // write temp block to dsik
    // assuming superblock always on the 0th memory location
    write_block(memory_location, 0, temp_block);
    return;
}
superblock::superblock(void * memory_location){
    this->init_superblock(memory_location,64,56,5,8, 3, 2,1);
}

superblock::superblock(void *memory_location, int tb, int db, int ib, int fdb, int fib, int dbd, int ibd) {
    this->init_superblock(memory_location,  tb,  db,  ib,  fdb, fib,  dbd, ibd);

}

void superblock::_repr(){
    printf("\nThe current SuperBlock is as follow : \nTotal Blocks : %d\nData Blocks : %d\n"
                   "Inode Blocks : %d\n"
                   "First Data Block : %d\n"
                   "First Inode Block : %d\n"
                   "Free Data Block : %d\n"
                   "Free Inode Block : %d\n",total_blocks,data_blocks,inode_blocks,first_data_block,first_inode_block,free_data_blocks,free_inode_blocks);
}
void superblock::init_superblock(void *memory_location,int tb, int db, int ib, int fdb, int fib, int dbd, int ibd) {
    total_blocks = tb;
    data_blocks = db;
    inode_blocks = ib;
    free_data_blocks = db;
    free_inode_blocks = ib;
    first_data_block = fdb;
    first_inode_block = fib;
    data_bitmap_block = dbd;
    inode_bitmap_block = ibd;
    inode_size = sizeof(inode_struct);
//    memory_location = allocate_memory_block(total_blocks);
    number_of_inodes = (inode_blocks*BLOCK_SIZE)/inode_size;
    inode_per_block = BLOCK_SIZE/inode_size;

    int inode_number = 0; // starting inode number;
    for (int i=0;i<inode_blocks;i++){
        // for each  block
        inode_struct *inode_this_block = (inode_struct *)malloc(inode_size * inode_per_block); // init the buffer memory we will init ree indoes in this memoy and thn ewrite it o the secondary memory
        for(int j=0;j<inode_per_block;j++){
            // init each inode for this block
            inode_this_block[j].block_size = BLOCK_SIZE;
            inode_this_block[j].inode = inode_number;
            inode_this_block[j].size = 0;
            inode_number++;


        }
        write_block(memory_location,first_inode_block + i, inode_this_block);

    }
    // init the bytemap for inode as all free
    // the bitmap of each is one size
//    uint8_t *temp_block = (uint8_t *)malloc(BLOCK_SIZE); // we will make the inode bitmap on this and then write it to the inode block
    bool *temp_block = (bool *)malloc(BLOCK_SIZE); // we will make the inode bitmap on this and then write it to the inode block

    for(int i=0;i<number_of_inodes;i++){ // for each inode init the bitmap
        temp_block[i] = 0; // assign each inode a value 0 in false in bool
    }

    write_block(memory_location, first_inode_block, temp_block);
    free(temp_block); // deallocate the memory
    // init the data bitmap
    temp_block = (bool *)malloc(BLOCK_SIZE);
    for(int i=0;i<data_blocks;i++){
        temp_block[i] = 0; // assign each block as free
    }
    write_block(memory_location, first_data_block, temp_block);
    free(temp_block);
    // write the superblock to the memory
    void * temp_block1 = malloc(BLOCK_SIZE);
    memcpy(temp_block1, this, sizeof(superblock));
    // write the temp block to 0 th block of storage
    write_block(memory_location,0, temp_block1);
    free(temp_block1);
}


void* make_fs(void *memory_location){
    superblock sp(memory_location);
    return memory_location;
}


void* make_fs(void *memory_location,int tb,int db,int ib,int fdb,int fib,int dbd,int ibd){
    superblock sp(memory_location, tb,db,ib,fdb,fib,dbd,ibd);
    return memory_location;

}

inode_struct inode_manager::inode_read(void*memory_location,int node_number){
    // assume the system call knows what it is doing
    // get the superblock for information
    superblock sb = superblock::read_superblock_fs(memory_location);


    // get the block number

    int relative_block_number = ((node_number*sizeof(inode_struct))/BLOCK_SIZE) ;
    int block_number = relative_block_number + sb.first_inode_block;
    // block number contans the block number contanin the inode node_number
    inode_struct *temp_block = (inode_struct *)malloc(BLOCK_SIZE);
    read_block(memory_location, block_number, temp_block);

    // the relative block on current block
    int relative_inode_on_block = node_number - relative_block_number*sb.inode_per_block;

    inode_struct inode = temp_block[relative_inode_on_block];
    return inode;


}

void inode_manager::inode_write(void *memory_location, inode_struct inode) {
    // @todo : Assuming that the system call calling the function will modiyfing the necessary section like the bitmap and data blocks
    // reading the superblock
    superblock sb = superblock::read_superblock_fs(memory_location);

    // calculate the block for inode
    int node_number = inode.inode; // the inode number
    int relative_block_number = ((node_number*sizeof(inode_struct))/BLOCK_SIZE) ;
    int block_number = relative_block_number + sb.first_inode_block;

    // the relative block on current block
    int relative_inode_on_block = node_number - relative_block_number*sb.inode_per_block;

    // read the whole block
    inode_struct *temp_block = (inode_struct *)malloc(BLOCK_SIZE);
    read_block(memory_location, block_number, temp_block);

    // change the item on block
    temp_block[relative_block_number] = inode;


    // write the changed block back to memory
    write_block(memory_location, block_number, temp_block);

    return ;
}

bool* bitmap_manager::read_inode_bitmap(void *memory_location) {
    // read the superblock
    superblock sb = superblock::read_superblock_fs(memory_location);

    // assign a memory for bitmap
    bool* temp_block = (bool*)malloc(BLOCK_SIZE);
    read_block(memory_location, sb.first_inode_block,temp_block);

    // return the bitmap pointer
    return temp_block;

}
bool* bitmap_manager::read_data_bitmap(void *memory_location) {
    // read the superblock
    superblock sb = superblock::read_superblock_fs(memory_location);

    // assign a memory for bitmap
    bool* temp_block = (bool*)malloc(BLOCK_SIZE);
    read_block(memory_location, sb.first_data_block,temp_block);

    // return the bitmap pointer
    return temp_block;

}
void bitmap_manager::write_inode_bitmap(void *memory_location, bool *bitmap) {
    // read superblock
    superblock sb = superblock::read_superblock_fs(memory_location);

    // we will correct the memory size mismatch
    bool* temp_block = (bool *)malloc(BLOCK_SIZE);
    memcpy(temp_block, bitmap, sb.number_of_inodes);

    // wrote it to temp_block
    // write the block to scondary storage
    write_block(memory_location,sb.first_inode_block,temp_block);

    free(temp_block);

    return ;

}

void bitmap_manager::write_data_bitmap(void *memory_location, bool *bitmap) {     
    // read superblock     
    superblock sb = superblock::read_superblock_fs(memory_location);

    // we will correct the memory size mismatch     
    bool* temp_block =(bool *)malloc(BLOCK_SIZE);     
    memcpy(temp_block, bitmap,sb.data_blocks);

    // wrote it to temp_block     // write the block to scondary storage
    write_block(memory_location,sb.first_data_block,temp_block);

    free(temp_block);

    return ; 
}

