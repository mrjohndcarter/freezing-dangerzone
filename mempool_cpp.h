#ifndef _XXXXX_MEMPOOL_CPP_H
#define _XXXXX_MEMPOOL_CPP_H

#include <stdio.h>
#include <time.h>

namespace MEMPOOL_CPP
{

class MemoryPool
{

public:

    MemoryPool(size_t poolSizeInBytes = 1024, size_t blockSizeInBytes = 4);
    virtual ~MemoryPool();

    void *allocate(size_t sizeInBytes);
    void mark(void);
    void free(time_t);

protected:

    size_t poolSize;
    size_t blockSize;

private:

    MemoryPool(MemoryPool &mp);
    void *poolRegion;

};

}

#endif

