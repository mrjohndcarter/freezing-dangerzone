CXXFLAGS=-Wall -pedantic -g

all: test_cpp MemoryPool.o Texture.o

MemoryPool.o: MemoryPool.h MemoryPool.cpp
	${CXX} ${CXXFLAGS} -c MemoryPool.cpp -o MemoryPool.o

Texture.o: Texture.h Texture.cpp
	${CXX} ${CXXFLAGS} -c Texture.cpp -o Texture.o

test_cpp: MemoryPool.o Texture.o mempooltest_cpp.o
	${CXX} ${LDFLAGS} MemoryPool.o Texture.o mempooltest_cpp.o -o test_cpp

clean:
	${RM} *.o
	${RM} test_cpp

# not working on yosemite
valgrind: test_cpp
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
	--num-callers=20 --track-fds=yes --dsymutil=yes ./test_c
