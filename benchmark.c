#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "mempool_c.h"

#define COUNT 10000

#include <sys/time.h>
#include <sys/resource.h>

/* http://stackoverflow.com/questions/2349776/how-can-i-benchmark-c-code-easily */
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

int main(void) {

    double t0 = get_time();
    int *anInt;

    for (long i = 0; i < COUNT; i++) {
        anInt = malloc(4096);
    }

    double t1 = get_time();
    double timeDelta = t1 - t0;

    printf("\n%lf\n", timeDelta);

    SF_MEMORYPOOL_T mpool;
    sf_init(&mpool, 4096 * COUNT, 4096);

    t0 = get_time();

    for (long i = 0; i < COUNT; i++) {
        anInt = sf_allocate(&mpool,4096);
    }

    t1 = get_time();

    timeDelta = t1 - t0;

    printf("\n%lf\n", timeDelta);


}
