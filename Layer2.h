#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <string.h>
#include "Layer1.h"

#ifndef CS342_PROJECT_LAYER2_H
#define CS342_PROJECT_LAYER2_H
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 4096 
#endif
#define INODE_SIZE 256

int createfile(void *memory_location,std::string name);
inode_struct fileopen(void *memory_location,int index_id);
#endif