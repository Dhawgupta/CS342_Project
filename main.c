//
// Created by dawg on 4/27/18.
//

#include <stdio.h>
#include "Layer0.h"
#include "Layer1.h"
#include <time.h>

int main() {
    void *mm;
    mm = allocate_memory_block(490);
    char buf[80];
    long t = time(NULL);
//    time(&t);
//    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &t);
    printf("Memory Location : %ld\n %d\n",mm,sizeof(struct inode_struct));
//    printf("Time : %s",buf);
    return 0;
}