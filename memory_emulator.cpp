//
// Created by dawg on 4/27/18.
//
// strucutre largely inspired from  : http://pages.cs.wisc.edu/~remzi/OSTEP/file-implementation.pdf
//#include <iostream>

/** This is represnetative of Layer 1
 * 1. Function to initialize the memory
 *      1.1 We need to init the size of the memory
 *      1.2 Divide the memory into various sections
 *          1.2.1 Data Section - Number of blocks and their corresponding ID's
 *          1.2.2 Inode Section - Section to Store Inodes // also allocate appropriate inodes
 *          1.2.3 Data Section Bitmap
 *          1.2.4 Inode Section Bitmap
 *          1.2.5 SuperBlock
 *      1.3
 */


#include <stdlib.h>
#include "Layer0.h"
#include <iostream>
#ifdef BLOCK_SIZE
#define BLOCK_SIZE 4096 // 4096 byte of block size
#endif
#define INODE_SIZE 256 // from the wisc docuemntation we are taking the inodes size as this


int main(int argc, char *argv[]){

}
