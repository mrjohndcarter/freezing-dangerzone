#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>

#include "MemoryPool.h"

namespace memory_pool
{

/* "C" interface */

/* block size should be chosen with regard to alignment */
void sf_init(SF_MEMORYPOOL_T *pool, size_t size, size_t blockSize)
{
    if (!pool) {
        /* error */
        return;
    }
    pool->size = size;
    pool->blockSize = blockSize;

    unsigned blockCount = pool->size / pool->blockSize;
    pool->region = malloc(blockCount * pool->blockSize);

    if (!pool->region) {
        pool->blocksAvailable = 0;
    }

    pool->nextFree = NULL;
    pool->firstBlock = NULL;

    for (int i = 0; i < blockCount; i++) {
        struct sf_memoryPoolEntry *newEntry = (struct sf_memoryPoolEntry *) \
                                              malloc(sizeof(struct sf_memoryPoolEntry));

        newEntry->region = (char *)pool->region + (i * blockSize);
        newEntry->timestamp = LONG_MAX;
        newEntry->next = pool->nextFree;
        pool->nextFree = newEntry;
    }
    pool->blocksAvailable = blockCount;
}

void sf_destroy(SF_MEMORYPOOL_T *pool)
{
    /* need to walk both lists to free entries */
    struct sf_memoryPoolEntry *temp = pool->nextFree;

    while (temp) {
        struct sf_memoryPoolEntry *next = temp->next;
        free(temp);
        temp = next;
    }

    temp = pool->firstBlock;

    while (temp) {
        struct sf_memoryPoolEntry *next = temp->next;
        free(temp);
        temp = next;
    }

    pool->blocksAvailable = 0;
    free(pool->region);
}

void *sf_allocate(SF_MEMORYPOOL_T *pool, size_t size)
{
    if (!pool->nextFree) {
        return NULL;
    }

    if (size > pool->blockSize) {
        return NULL;
    }

    /* get next free block */
    struct sf_memoryPoolEntry *temp = \
                                      (struct sf_memoryPoolEntry *) pool->nextFree;

    /* mark it as never expiring */
    temp->timestamp = LONG_MAX;

    /* decrement blocks available */
    pool->blocksAvailable--;

    /* remove it from free list */
    pool->nextFree = (struct sf_memoryPoolEntry *) temp->next;

    /* insert block at head of in use list */
    temp->next = (struct sf_memoryPoolEntry *) pool->firstBlock;
    pool->firstBlock = (struct sf_memoryPoolEntry *) temp;

    /* @TODO memset */

    return temp->region;
}

void sf_mark(SF_MEMORYPOOL_T *pool, time_t timestamp)
{
    int count = 0;
    struct sf_memoryPoolEntry *cursor = pool->firstBlock;
    while (cursor) {
        cursor->timestamp = timestamp;
        cursor = cursor->next;
        count++;
    }
}

void sf_free(SF_MEMORYPOOL_T *pool, time_t timestamp)
{
    struct sf_memoryPoolEntry *cursor;
    struct sf_memoryPoolEntry *temp;
    struct sf_memoryPoolEntry *last = NULL;

    cursor = pool->firstBlock;

    while (cursor) {

        if (cursor->timestamp < timestamp) {

            if (!last) {
                pool->firstBlock = cursor->next;
            } else {
                last->next = cursor->next;
            }

            /* return that block to free list */
            temp = cursor->next;

            /* add cursor to head of free list */
            cursor->next = pool->nextFree;
            pool->nextFree = cursor;

            /* step cursor forward */
            cursor = temp;

            pool->blocksAvailable++;

        } else {
            /* skip it */
            last = cursor;
            cursor = cursor->next;
        }
    }
}

/* Memory Pool Stuff */

MemoryPool::MemoryPool(size_t totalSizeInBytes, size_t blockSizeInBytes)
{
    sf_init(&managedPool, totalSizeInBytes, blockSizeInBytes);
}
MemoryPool::~MemoryPool()
{
    sf_destroy(&managedPool);
}

void *MemoryPool::allocate(size_t sizeInBytes)
{
    return sf_allocate(&managedPool, sizeInBytes);
}

void MemoryPool::mark(time_t timestamp)
{
    return sf_mark(&managedPool, timestamp);
}

void MemoryPool::purge(time_t timestamp)
{
    return sf_free(&managedPool, timestamp);
}

unsigned MemoryPool::availableBlocks(void) {
    return managedPool.blocksAvailable;
}


}
