#ifndef _XXXXX_MEMPOOL_C_H
#define _XXXXX_MEMPOOL_C_H

#include <stdio.h>
#include <time.h>

/* 24 bytes */

struct memoryPoolEntry {

    void *region;
    time_t timestamp;
    struct memoryPoolEntry *next;

};

typedef struct memoryPoolEntry MEMORYPOOL_ENTRY_T;

typedef struct {

    size_t size;
    size_t blockSize;
    unsigned blocksAvailable;
    void *region;
    struct MEMORYPOOL_ENTRY_T *nextFree;
    struct MEMORYPOOL_ENTRY_T *firstBlock;

} MEMORYPOOL_T;

void cinit(MEMORYPOOL_T *pool, size_t size, size_t blockSize);

void cdestroy(MEMORYPOOL_T *pool);

void *callocate(MEMORYPOOL_T *pool, size_t size);

void cmark(MEMORYPOOL_T *pool, int timestamp);

void cfree(MEMORYPOOL_T *pool, int timestamp);

#endif
