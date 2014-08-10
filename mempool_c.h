#ifndef _XXXXX_MEMPOOL_C_H
#define _XXXXX_MEMPOOL_C_H

#include <stdio.h>

void *allocate(size_t size);
 
void mark(int timestamp);

void free(int timestamp);

#endif
