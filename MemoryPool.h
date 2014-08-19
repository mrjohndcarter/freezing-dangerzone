
#include <stdio.h>
#include <time.h>

#include "mempool_c.h"

#ifndef _XXXXX_MEMPOOL_CPP_H
#define _XXXXX_MEMPOOL_CPP_H

namespace memory_pool
{

/**
 * (S)tatic (F)ixed block size memory pool.
 */

/* 24 bytes -- will align to 8 bytes */
/* note: because we preallocate we can't use usual union approach */

struct sf_memoryPoolEntry {
    void *region; /* 8 */
    time_t timestamp; /* 8 */
    struct sf_memoryPoolEntry *next; /* 8 */
};

/* 48 bytes -- will align to 8 bytes -- 4 available */

typedef struct {
    size_t size; /* 8 */
    size_t blockSize; /* 8 */
    unsigned blocksAvailable; /* 4 */
    void *region; /* 8 */
    struct sf_memoryPoolEntry *nextFree; /* 8 */
    struct sf_memoryPoolEntry *firstBlock; /* 8 */

} SF_MEMORYPOOL_T;

/**
 * sf_init
 *
 * initialize a memory pool.
 *
 * @param pool - pointer to pool, of type SF_MEMORYPOOL_T
 * @param size - size of memory pool in bytes.
 * @param blockSize - maximum size for region allocated by this pool.
 */

void sf_init(SF_MEMORYPOOL_T *pool, size_t size, size_t blockSize);

/**
 * sf_destroy
 *
 * clean up and deallocate a memory pool.
 * @param pool - pointer to pool, of type SF_MEMORYPOOL_T
 */

void sf_destroy(SF_MEMORYPOOL_T *pool);

/**
 * sf_allocate
 *
 * allocate a memory region of size bytes.
 * @param pool - pointer to pool, of type SF_MEMORYPOOL_T
 */

void *sf_allocate(SF_MEMORYPOOL_T *pool, size_t size);

/**
 * sf_mark
 *
 * mark all memory currently allocated, with the specified timestamp.
 * @param pool - pointer to pool, of type SF_MEMORYPOOL_T
 * @param timestamp - time to mark allocations with, in seconds since epoch.
 */

void sf_mark(SF_MEMORYPOOL_T *pool, time_t timestamp);

/**
 * sf_free
 *
 * allocate a memory region of size bytes.
 * @param pool - pointer to pool, of type SF_MEMORYPOOL_T
 * @param timestamp - time to mark allocations with, in seconds since epoch.
 */

void sf_free(SF_MEMORYPOOL_T *pool, time_t timestamp);

/** MemoryPool
 *
 * C++ wrapper for above sf_* functions.
 */

class MemoryPool
{

public:
    MemoryPool(size_t totalSizeInBytes, size_t blockSizeInBytes);
    ~MemoryPool();

    void *allocate(size_t sizeInBytes);
    void mark(time_t timestamp);
    void purge(time_t timestamp);

private:
    MemoryPool(MemoryPool &);
    SF_MEMORYPOOL_T managedPool;
};

/** Base class for Pooled Objects
 *
 */

class PooledObject
{

public:
    PooledObject();
    virtual ~PooledObject();

protected:
    MemoryPool *myPool;
};



}

#endif
