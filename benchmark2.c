#include <stdio.h>
// #include <time.h>
// #include <unistd.h>
// #include <stdlib.h>

// #include "mempool_c.h"

// #define COUNT 10000

// #include <sys/time.h>
// #include <sys/resource.h>

// /* http://stackoverflow.com/questions/2349776/how-can-i-benchmark-c-code-easily */
// double get_time()
// {
//     struct timeval t;
//     struct timezone tzp;
//     gettimeofday(&t, &tzp);
//     return t.tv_sec + t.tv_usec*1e-6;
// }

int main(int argc, char **argv) {

    bool useMalloc = true;
    long iterations = 0;

    if (argc <= 1) {
        printf("\nUsage: (malloc | pool) (iterations)");
        return 0;
    }

    /* parse type of test, malloc or custom pool */
    if (strcmp(argv[1], "malloc") == 0) {
        useMalloc = true;
    }
    else if (strcmp(argv[1], "pool") == 0) {
        useMalloc = false;
    }
    else {
        printf("\nUnknown option %s", argv[1]);
        return 0;
    }
    
    /* how many iterations ? */
    iterations = atol(argv[2]);
}
