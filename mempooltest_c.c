#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "mempool_c.h"

int main(void)
{
    printf("* Mempool C Test *");
    SF_MEMORYPOOL_T mpool;
    time_t timeStamp;
    sf_init(&mpool, 1024, 8);

    for (int i = 0; i < (int)1024 / 8; i++) {
        int *t = sf_allocate(&mpool, sizeof(int));
        *t = i;

        if (i == 8) {
            time(&timeStamp);
            sf_mark(&mpool, timeStamp);
        }
    }

    sleep(1);
    time(&timeStamp);
    sf_free(&mpool, timeStamp);
    sf_destroy(&mpool);
    printf("\n");
    return 0;
}
