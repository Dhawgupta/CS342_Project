#include <stdio.h>
#include <iostream>

#include "Layer0.h"
#include "Layer1.h"

using namespace std;
int main() {
    void *mm;
    mm = allocate_memory_block(490);
    cout<<mm<<endl;
    return 0;
}