//
// Created by dawg on 4/27/18.
//
/** This is represnetative of Layer 1
 * 1. Function to initialize the memory
 *      1.1 We need to init the size of the memory
 *      1.2 Divide the memory into various sections
 *          1.2.1 Data Section - Number of blocks and their corresponding ID's (n blocks)
 *          1.2.2 Inode Section - Section to Store Inodes // also allocate appropriate inodes (m blocks)
 *          1.2.3 Data Section Bitmap (1 Block)
 *          1.2.4 Inode Section Bitmap (1 Block)
 *          1.2.5 SuperBlock (1 Block)
 *      1.3
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#ifndef CS342_PROJECT_LAYER1_H
#define CS342_PROJECT_LAYER1_H
#ifdef BLOCK_SIZE
#define BLOCK_SIZE 4096 // 4096 byte of block size
#endif
#define INODE_SIZE 256 // from the wisc docuemntation we are taking the inodes size as this


struct inode_struct{
    int inode;
    int file_type; // directory of file type 0 (file) and  1 (directory)
    int permission;// Of type 0664 i.e. -rw-rw-r--
    int nlinks; // the number of links
    int block_size;
    int uid;
    int gid;
    int size; // the size of files in byte
    int blocks; // the number of blocks the file uses
    void *direct_p[5]; // 12 direct pointers for memory
    void *first_p; // one indirect pointe
    void *second_p;
    void *three_p;
    time_t modified; // the var of time using time(NULL); strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts); // buf contains the string  buf[80]
    time_t created;
    time_t written;

}; // currently each inode is 128 Bytes
//superblock will start at 0 th blcok
// https://www.nongnu.org/ext2-doc/ext2.html#SUPERBLOCK
class superblock{ // structure represeting the filesystem
public:
    int total_blocks; // total number of blocks
    int data_blocks; // total number of data blocks
    int inode_blocks; // total number of inode blocks
    int free_data_blocks; // free data blocks
    int free_inode_blocks; // free inodes blocks
    int first_data_block; // first data block number
    int first_inode_block; // first inode block
    int data_bitmap_block;
    int inode_bitmap_block;
    int inode_size;
    /**
     * This function will be used to init the filesystem , superblock will reside block0
     * all the approaprate entries will be updated accordinlglgt
     *
     * @param1 total_blocks
     * @param2 data_block
     * @param3 inode_block
     * @param4 first_data_block
     * @param5 first_inode_block
     * @param6 data_bitmap_block
     * @param7 inode_bitmap_block
     */
    void init_superblock(int tb,int db,int ib,int fdb,int fib,int dbd,int ibd);





};
#endif //CS342_PROJECT_LAYER1_H
