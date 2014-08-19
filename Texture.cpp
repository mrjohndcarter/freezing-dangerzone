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

void Texture::printTexture()
{
    for (int i = 0; i < POOLED_TEXTURE_MAX_HEIGHT; i++) {
        std::cout << "\n";
        for (int j = 0; j < POOLED_TEXTURE_MAX_WIDTH; j++) {
            std::cout << texture[(i * POOLED_TEXTURE_MAX_HEIGHT) + j];
        }
    }
}

TextureFactory::TextureFactory(int maxTexturesInPool) :
    factoryPool(maxTexturesInPool * sizeof(Texture), sizeof(Texture))
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

void TextureFactory::purge(time_t timestamp)
{
    factoryPool.mark(timestamp);
}



}
