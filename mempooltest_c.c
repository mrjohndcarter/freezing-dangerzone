#include <stdio.h>

#include "mempool_c.h"

int main(void)
{
    printf("Mempool C test.");

    MEMORYPOOL_T mpool;
    cinit(&mpool, 1024, 8);

    int *d = callocate(&mpool, sizeof(int));
    *d = 77;

    printf("\nd = %d", *d);

    int *e = callocate(&mpool, sizeof(int));
    *e = 88;

    printf("\ne = %d", *e);

    cdestroy(&mpool);

    return 0;
}
