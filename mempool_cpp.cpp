
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
    poolRegion = ::operator new(poolSize, std::nothrow);

    if (!poolRegion) {
        void *allocate(size_t sizeInBytes);

        /* do something dramatic */
        abort();
    }
    memset(poolRegion, 0, poolSize);
}

MemoryPool::~MemoryPool()
{
    ::operator delete(poolRegion);
    poolRegion = NULL;
}

void *MemoryPool::allocate(size_t sizeInBytes)
{
    /* @TODO */
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
