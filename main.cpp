#include <string.h>
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Layer0.h"
#include "Layer1.h"

using namespace std;
// hello
int main() {
    void *mm;
    mm = allocate_memory_block(64); // allocation of 1000 blocks of mempry
    void *read = malloc(BLOCK_SIZE);  // allcoate blocks to read
    void *write = malloc(BLOCK_SIZE); // allocate blocks to write
    strcpy((char *)write,"This is a sample data to experiment the writing capabilites of thhe function");
    cout<<(char *)write<<endl;
    write_block(mm, 10,write);
    read_block(mm,10,read);
    cout<<(char *)read<<endl;
    superblock s(mm); // init the superblock;
    s._repr();
    void *temp_block = malloc(BLOCK_SIZE);
    cout<<endl<<"Showing the read superblock " <<endl;
    read_block(mm, 0, temp_block);
    superblock *sp = (superblock*)malloc(sizeof(superblock));
    memcpy(sp, temp_block,sizeof(superblock));
    sp->_repr();

    sp->total_blocks = 100;
    superblock::write_superblock_fs(mm, *sp);
    superblock sp2 = superblock::read_superblock_fs(mm);
    sp2._repr();
    return 0;
}