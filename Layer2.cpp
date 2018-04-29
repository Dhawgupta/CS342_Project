#include "Layer1.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <time.h>
using namespace std;

int createfile(void *memory_location,string name){
	superblock sb = superblock::read_superblock_fs(memory_location);
	int offset=sb.inode_bitmap_block;
	bool *bitmap = bitmap_manager::read_inode_bitmap((void*)((char *)memory_location+offset*BLOCK_SIZE));
	int index_id=-1,data_id=-1;
	for(int i=0;i<BLOCK_SIZE;i++){
		if(!bitmap[i]){
			index_id=i;
			break;
		}
	}
	offset=sb.data_bitmap_block;
	bitmap=bitmap_manager::read_data_bitmap((void*)((char *)memory_location+offset*BLOCK_SIZE));
	for(int i=0;i<BLOCK_SIZE;i++){
		if(!bitmap[i]){
			data_id=i;
			break;
		}
	}
	if(index_id==-1 || data_id==-1)
		return -1;
	offset=sb.data_bitmap_block+1;
	inode_struct iblock=inode_manager::inode_read(memory_location,index_id);
	iblock.inode=index_id;
	iblock.file_type=0;
	iblock.permission=0664;
	iblock.nlinks=1;
	iblock.block_size=BLOCK_SIZE;
	iblock.blocks=1;
	iblock.direct_p[0]=(void*)((char *)memory_location+offset*BLOCK_SIZE);
	iblock.created=iblock.modeified=iblock.written=time(0);
	return index_id;
}
inode_struct fileopen(void *memory_location,int index_id){	
	inode_struct iblock=inode_manager::inode_read(memory_location,index_id);
	return iblock;
}