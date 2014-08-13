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
    pool->region = malloc(size);

    if (!pool->region) {
        pool->blocksAvailable = 0;
    }

    pool->nextFree = NULL;
    pool->firstBlock = NULL;

    for (int i = blockCount; i >= 0; i--) {
        //MEMORYPOOL_ENTRY_T *temp = pool->firstBlock;
        struct memoryPoolEntry *newEntry = malloc(sizeof(struct memoryPoolEntry));
        newEntry->region = (char *)pool->region + (i * blockSize);
        newEntry->timestamp = LONG_MAX;
        newEntry->next = (struct memoryPoolEntry *) pool->nextFree;
        pool->nextFree = (struct memoryPoolEntry *) newEntry;
    }
    pool->blocksAvailable = blockCount;
}

void cdestroy(MEMORYPOOL_T *pool)
{
    /* need to walk both lists to free entries */
    struct memoryPoolEntry *temp = (struct memoryPoolEntry *) pool->nextFree;

    while (temp) {
        struct memoryPoolEntry *next = temp->next;
        free(temp);
        temp = next;
    }
    temp = (struct memoryPoolEntry *) pool->firstBlock;

    while (temp) {
        struct memoryPoolEntry *next = temp->next;
        free(temp);
        temp = next;
    }
    free(pool->region);
}

void *callocate(MEMORYPOOL_T *pool, size_t size)
{
    if (!pool->nextFree) {
        return NULL;
    }
    /* get next free block */
    struct memoryPoolEntry *temp = (struct memoryPoolEntry *) pool->nextFree;

    /* mark it as never expiring */
    temp->timestamp = LONG_MAX;

    /* remove it from free list */
    pool->nextFree = (struct memoryPoolEntry *) temp->next;

    /* insert block at head of in use list */
    temp->next = (struct memoryPoolEntry *) pool->firstBlock;
    pool->firstBlock = (struct memoryPoolEntry *) temp;

    return temp->region;
}

void cmark(MEMORYPOOL_T *pool, int timestamp)
{

}

void cfree(MEMORYPOOL_T *pool, int timestamp)
{

}

