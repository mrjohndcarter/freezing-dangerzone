#include <stdio.h>

#include "mempool_c.h"

int main(void)
{
    printf("Mempool C test.");

    MEMORYPOOL_T mpool;
    cinit(&mpool, 1024, 8);

    // int *d = callocate(&mpool, sizeof(int));
    // *d = 77;

    // printf("\nd = %d", *d);

    // int *e = callocate(&mpool, sizeof(int));
    // *e = 88;

    //printf("\ne = %d", *e);

    for (int i = 0; i < (int)1024 / 8; i++) {
        int *t = callocate(&mpool, sizeof(int));
        *t = i;
        printf("%d,", *t);
    }

    cdestroy(&mpool);

    return 0;
}
