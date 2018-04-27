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
    
}



/*
int main(int argc, char *argv[]){
    printf("Size of Different Data Types : \nInt : %d\nFloat : %d\nChar : %d\nPtr : %d",sizeof(int), sizeof(float), sizeof(long), sizeof(int *));
    int blocks = 64;
    void  *memory = allocate_memory_block(blocks);
//    printf("",memory);


}
 */

