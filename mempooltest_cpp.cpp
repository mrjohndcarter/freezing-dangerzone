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
    
    example_usage::Texture *t;

    t = new example_usage::Texture;

    t->loadTexture(randomTexture());

    t->printTexture();

    delete t;

    return 0;



}

