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


superblock::superblock(void * memory_location){
    this->init_superblock(memory_location,64,56,5,8, 3, 2,1);
}

superblock::superblock(void *memory_location, int tb, int db, int ib, int fdb, int fib, int dbd, int ibd) {
    this->init_superblock(memory_location,  tb,  db,  ib,  fdb, fib,  dbd, ibd);

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
//    uint8_t temp_block = (uint8_t *)malloc(BLOCK_SIZE);
    // the bitmap of each is one size
    uint8_t *temp_block = (uint8_t *)malloc(BLOCK_SIZE); // we will make the inode bitmap on this and then write it to the inode block
    for(int i=0;i<number_of_inodes;i++){ // for each inode init the bitmap
        temp_block[i] = 0; // assign each inode a value 0 in byte amp

    }
    write_block(memory_location, first_inode_block, temp_block);
    free(temp_block); // deallocate the memory
    // init the data bitmap
    temp_block = (uint8_t *)malloc(BLOCK_SIZE);
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


void make_fs(void *memory_location){
    superblock( )
}



/*
int main(int argc, char *argv[]){
    printf("Size of Different Data Types : \nInt : %d\nFloat : %d\nChar : %d\nPtr : %d",sizeof(int), sizeof(float), sizeof(long), sizeof(int *));
    int blocks = 64;
    void  *memory = allocate_memory_block(blocks);
//    printf("",memory);


}
 */

