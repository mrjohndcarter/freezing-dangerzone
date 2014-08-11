
#include "mempool_cpp.h"

#include <stdlib.h>
#include <string.h>

#include <new>

namespace MEMPOOL_CPP
{

MemoryPool::MemoryPool(size_t poolSizeInBytes, size_t blockSizeInBytes) :
    poolSize(poolSizeInBytes),
    blockSize(blockSizeInBytes)
{
    blockCount = (int)(poolSizeInBytes / blockSizeInBytes);
    region = new (std::nothrow) char[poolSizeInBytes];


    if (!region) {
        /* allocation failed -- do something dramatic */
        abort();
    }
    memset(region, 0, poolSize);

    //REGION_LIST_ENTRY_T *blockList[] = new (std::nothrow) REGION_LIST_ENTRY_T*[blockCount];

    blocksList = new (std::nothrow) REGION_LIST_ENTRY_T*[blockCount];

    /* @TODO check */

    for (int i = 0; i < blockCount; i++) {

        blocksList[i] = new REGION_LIST_ENTRY_T;

        blocksList[i]->timestamp = 0;
        blocksList[i]->block = region + (blockSize * i);
        if (i != (blockCount - 1)) {
            blocksList[i]->nextBlock = blocksList[i+1];
        }
        else {
            blocksList[i]->nextBlock = NULL;
        }
    }
    firstBlock = (REGION_LIST_ENTRY_T *) region;
    firstBlock->block = region;
    firstBlock->timestamp = 0;
    firstBlock->nextBlock = NULL;
    firstFreeBlock = firstBlock;
}

MemoryPool::~MemoryPool()
{
    ::operator delete(region);
    region = NULL;
}

void *MemoryPool::allocate(size_t sizeInBytes)
{
    /* @TODO */
    /* check blocks available */
    return ::operator new(sizeInBytes, std::nothrow);
}

void MemoryPool::mark(void)
{
    /* @TODO */
}

void MemoryPool::free(time_t)
{
    /* @TODO */
}


}
