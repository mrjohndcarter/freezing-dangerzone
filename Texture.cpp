#include "Texture.h"

#include <iostream>

namespace example_usage
{

memory_pool::MemoryPool *Texture::objectPool = NULL;

Texture::Texture() {
    myPool = Texture::pool();
}

memory_pool::MemoryPool *Texture::pool(void)
{
    if (!objectPool) {
       Texture::objectPool = new memory_pool::MemoryPool(SIMULTANEOUS_POOLED_TEXTURES, sizeof(Texture));
    }
    return Texture::objectPool;
}

void Texture::loadTexture(int *texture) {
    memcpy(this->texture, texture, POOLED_TEXTURE_SIZE * sizeof(int));
}

void Texture::printTexture() {
    for (int i = 0; i < POOLED_TEXTURE_MAX_HEIGHT; i++) {
        std::cout << "\n";
        for (int j = 0; j < POOLED_TEXTURE_MAX_WIDTH; j++) {
            std::cout << texture[(i * POOLED_TEXTURE_MAX_HEIGHT) + j];
        }
    }
}


}
