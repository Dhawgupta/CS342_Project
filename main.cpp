
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Layer0.h"
#include "Layer1.h"

using namespace std;

int main() {
    void *mm;

    mm = allocate_memory_block(64); // allocation of 1000 blocks of mempry
    void *read = malloc(BLOCK_SIZE);  // allcoate blocks to read
    void *write = malloc(BLOCK_SIZE); // allocate blocks to write
//    strc
    strcpy((char *)write,"This is a sample data to experiment the writing capabilites of thhe function");
    cout<<(char *)write<<endl;
    write_block(mm, 10,write);
    read_block(mm,10,read);
    cout<<(char *)read<<endl;
    cout<<"Size of SuperBlock : "<<sizeof(superblock)<<endl;
    superblock sp(mm);
    cout<<"Size of SuperBlock : "<<sizeof(sp)<<" "<<sp.first_data_block<<endl;



    return 0;
}