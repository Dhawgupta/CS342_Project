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


void superblock::init_superblock(int tb, int db, int ib, int fdb, int fib, int dbd, int ibd) {
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
    memory_location = allocate_memory_block(total_blocks);
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

    // init the bitmap for inode as all free
    


    // init the memory


}



/*
int main(int argc, char *argv[]){
    printf("Size of Different Data Types : \nInt : %d\nFloat : %d\nChar : %d\nPtr : %d",sizeof(int), sizeof(float), sizeof(long), sizeof(int *));
    int blocks = 64;
    void  *memory = allocate_memory_block(blocks);
//    printf("",memory);


}
 */

