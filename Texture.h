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
    Texture(int identifer);
    void loadTexture(int *texture);
    void printTexture();

protected:

    int id;
    int texture[POOLED_TEXTURE_SIZE]; /* assume 1 byte each for RGBA */
};


class TextureFactory {

public:
    TextureFactory(int maxTexturesInPool);

    Texture* create(int identifier);
    void mark(time_t timestamp);
    void purge(time_t timestamp);

protected:

    memory_pool::MemoryPool factoryPool;
};


}
