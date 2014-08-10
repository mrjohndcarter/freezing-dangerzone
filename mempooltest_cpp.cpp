#include "mempool_cpp.h"

#include <iostream>

int main(void) {
    std::cout << "Mempool CPP test.";

    MEMPOOL_CPP::MemoryPool poolA;

    char *aString = (char *)poolA.allocate(sizeof(char) * 30);
    strcpy(aString, "hello world");
    std::cout << aString;

    return 0;
}
