#include "Texture.h"

#include <iostream>

namespace example_usage
{

Texture::Texture(int identifier) : id(identifier)
{
}

void Texture::loadTexture(int *texture)
{
    memcpy(this->texture, texture, POOLED_TEXTURE_SIZE * sizeof(int));
}

TextureFactory::TextureFactory(int maxTexturesInPool) :
    factoryPool(maxTexturesInPool *sizeof(Texture), sizeof(Texture))
{
}

Texture *TextureFactory::create(int identifier)
{
    void *region = factoryPool.allocate(sizeof(Texture));
    Texture *t = new(region) Texture(identifier);
    return t;
}

void TextureFactory::mark(time_t timestamp)
{
    factoryPool.mark(timestamp);
}

void TextureFactory::free(time_t timestamp)
{
    factoryPool.free(timestamp);
}

unsigned TextureFactory::availableBlocks(void)
{
    return factoryPool.availableBlocks();
}

}
