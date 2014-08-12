#include "mempool_c.h"

#include <limits.h>
#include <stdlib.h>

#define CEILING(x,y) (((x) + (y) - 1) / (y))


/* block size should be chosen with regard to alignment */
void cinit(MEMORYPOOL_T *pool, size_t size, size_t blockSize)
{
    if (!pool) {
        /* error */
        return;
    }

    pool->size = size;
    pool->blockSize = blockSize;

    unsigned blockCount = pool->size / pool->blockSize;

    printf("\n%d", blockCount);

    MEMORYPOOL_ENTRY_T *currentBlock;

    pool->region = malloc(size);

    if (!pool->region) {
        pool->blocksAvailable = 0;
    }

    pool->nextFree = malloc(sizeof(MEMORYPOOL_ENTRY_T));
    currentBlock = (MEMORYPOOL_ENTRY_T *) pool->nextFree;
    currentBlock->region = pool->region; /* memory region is first block */
    currentBlock->next = NULL;

    for (unsigned i = 1; i < blockCount; i++) {
        MEMORYPOOL_ENTRY_T *temp = malloc(sizeof(MEMORYPOOL_ENTRY_T));
        temp->region = (char *)pool->region + (i * blockSize);
        temp->next = NULL;
        currentBlock->next = (MEMORYPOOL_ENTRY_T *) temp;
    }
    // pool->blocksAvailable = blockCount;
    // pool->firstBlock = NULL;
}

void cdestroy(MEMORYPOOL_T *pool)
{
    free(pool->region);
}

void *callocate(MEMORYPOOL_T *pool, size_t size)
{
    // if (!pool->nextFree) {
    //     return NULL;
    // }

    // MEMORYPOOL_ENTRY_T *temp = pool->nextFree;
    // temp->timestamp = LONG_MAX;

    // temp->next = pool->firstBlock;
    // pool->firstBlock = temp;
    // pool->nextFree = temp->next;
    // return temp->region;
    //return NULL;
    return malloc(size);
}

void cmark(MEMORYPOOL_T *pool, int timestamp)
{

}

void cfree(MEMORYPOOL_T *pool, int timestamp)
{

}

