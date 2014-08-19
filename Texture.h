#include "MemoryPool.h"

#include <iostream>

/* constants used for the Texture class */

const int POOLED_TEXTURE_MAX_WIDTH = 256;
const int POOLED_TEXTURE_MAX_HEIGHT = 256;
const int POOLED_TEXTURE_SIZE = POOLED_TEXTURE_MAX_WIDTH *\
                                POOLED_TEXTURE_MAX_HEIGHT;

namespace example_usage
{

/**
 * Texture
 *
 * Represents a texture.
 * Not really.  It's a candidate for the worst texture class ever, it really
 * just exists to consume memory.
 */

class Texture
{
    friend inline std::ostream &operator<<(std::ostream &os,
                                           const example_usage::Texture &t);
public:
    Texture(int identifer);
    void loadTexture(int *texture);

protected:
    int id;
    int texture[POOLED_TEXTURE_SIZE]; /* assume 1 byte each for RGBA */
};

inline std::ostream &operator<<(std::ostream &os,
                                const example_usage::Texture &t)
{
    os << "id: " << t.id;
    for (int i = 0; i < POOLED_TEXTURE_MAX_HEIGHT; i++) {
        os << "\n";
        for (int j = 0; j < POOLED_TEXTURE_MAX_WIDTH; j++) {
            os << t.texture[(i * POOLED_TEXTURE_MAX_HEIGHT) + j];
        }
    }
    return os;
}

/**
 * TextureFactory
 *
 * Creates and allocates above textures.
 * Uses a very loose interpretation of the factory pattern.
 *
 * Not a singleton (Will allow multiple texture pools.)
 *
 * Manages the pool of allocate textures, allows you to call mark, free
 * on everything allocated to that point.
 */

class TextureFactory
{
    friend inline std::ostream &operator<<(std::ostream &os,
                                           const example_usage::TextureFactory &tp);
public:
    TextureFactory(int maxTexturesInPool);

    Texture *create(int identifier);
    void mark(time_t timestamp);
    void free(time_t timestamp);

    unsigned availableBlocks(void);

protected:
    memory_pool::MemoryPool factoryPool;
};

inline std::ostream &operator<<(std::ostream &os,
                                const example_usage::TextureFactory &tp)
{
    os << "\n=================" << tp.factoryPool << "\n=================";
    return os;
}

}
