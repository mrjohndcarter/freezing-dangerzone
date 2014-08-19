/* Very basic test of CPP interface */

#include <time.h>
#include <stdlib.h>

#include "Texture.h"

int *randomTexture()
{
    int *texture = (int *)malloc(sizeof(int) * POOLED_TEXTURE_SIZE);
    for (int i = 0; i < POOLED_TEXTURE_SIZE; i++) {
        texture[i] = rand() % 2;
    }
    return texture;
}

int main(void)
{
    srand(time(NULL));
    example_usage::TextureFactory tf(4);

    int count = 0;

    example_usage::Texture *t;

    while ((t = tf.create(count++))) {
        t->loadTexture(randomTexture());
        std::cout << "\n\n" << *t;
    }

    t = tf.create(count++); /* this should fail */

    if (!t) {
        std::cout << "\npoolSize+1 allocation failed. (YAY!)";
    } else {
        std::cout << "\nAllocation succeedded (BOO-URNS).";
    }

    std::cout << "\n";
    std::cout << tf;

    tf.mark(1000);
    tf.purge(2000);

    std::cout << "\n";
    std::cout << tf;

    t = tf.create(count++);

    if (!t) {
        std::cout << "\nAfter empty allocation failed. (BOO-URNS!)";
    } else {
        std::cout << "\nAfter empty allocation succeedded (YAY!).";
    }
}



