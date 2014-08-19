#include <time.h>
#include <stdlib.h>

#include "Texture.h"

int *randomTexture() {
    int *texture = (int *)malloc(sizeof(int) * POOLED_TEXTURE_SIZE);
    for (int i = 0; i < POOLED_TEXTURE_SIZE; i++) {
        texture[i] = rand() % 2;
    }
    return texture;
}


int main(void) {

    srand(time(NULL));
    example_usage::TextureFactory tf(16);
    example_usage::Texture *t = tf.create(0);
    t->loadTexture(randomTexture());
    t->printTexture();
}

