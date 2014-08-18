#include "MemoryPool.h"

#include <iostream>

const int SIMULTANEOUS_POOLED_TEXTURES = 256;
const int POOLED_TEXTURE_MAX_WIDTH = 4;
const int POOLED_TEXTURE_MAX_HEIGHT = 4;
const int POOLED_TEXTURE_SIZE = POOLED_TEXTURE_MAX_WIDTH *\
                                POOLED_TEXTURE_MAX_HEIGHT;

namespace example_usage
{

class Texture : public memory_pool::PooledObject
{
public:

    Texture();

    static memory_pool::MemoryPool *pool(void);

    inline void *operator new(size_t size)
    {
        return malloc(size);
        pool() ? pool()->allocate(size) : NULL;
    }

    inline void operator delete(void *p)
    {
        /* nothing to do */
    }

    void loadTexture(int *texture);

    void printTexture();

protected:

    int texture[POOLED_TEXTURE_SIZE]; /* assume 1 byte each for RGBA */
    static memory_pool::MemoryPool *objectPool;
};

}
