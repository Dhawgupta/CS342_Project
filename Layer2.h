#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <string.h>

#ifndef CS342_PROJECT_LAYER2_H
#define CS342_PROJECT_LAYER2_H
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 4096 
#endif
#define INODE_SIZE 256

void* mkdir(void *addr);

#endif