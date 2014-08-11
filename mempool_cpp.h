#ifndef _XXXXX_MEMPOOL_CPP_H
#define _XXXXX_MEMPOOL_CPP_H

#include <stdio.h>
#include <time.h>

namespace MEMPOOL_CPP
{

/* MemoryPool
 * ==========
 * Static MemoryPool.  Allocates regions of a fixed size.
 * Requests for larger regions fail.
 *
 * Meant to be combined to former a larger MemoryPool mechanism.
 * 
 * Aligned to blockSizeInBytes.
 */

class MemoryPool
{

public:

    MemoryPool(size_t poolSizeInBytes = 1024, size_t blockSizeInBytes = 64);
    virtual ~MemoryPool();

    /* Pool operations */
    void *allocate(size_t sizeInBytes);
    void mark(void);
    void free(time_t);

protected:

    size_t poolSize;
    size_t blockSize;

    struct REGION_LIST_ENTRY_T {

        char *block;
        struct REGION_LIST_ENTRY_T *nextBlock;
        time_t timestamp;

    };

    char *region;

    REGION_LIST_ENTRY_T **blocksList;

private:

    /* Let's just not deal with copying */
    MemoryPool(MemoryPool &mp);

    int blockCount;

    /* Pointer to first element of linked list */
    REGION_LIST_ENTRY_T *firstBlock;
    REGION_LIST_ENTRY_T *firstFreeBlock;
};

}

#endif

