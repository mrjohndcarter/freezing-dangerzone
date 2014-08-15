CFLAGS=-std=c99 -Wall -pedantic -g
CXXFLAGS=-Wall -pedantic -g
#PACKAGE_LIB_DIR=/Users/jcarter/Development/freezing-dangerzone
PACKAGE_LIB_DIR=/home/jcarter/temp/freezing-dangerzone

all: test_c benchmark

mempool_c.o: mempool_c.h mempool_c.c
	${CC} ${CFLAGS} -c mempool_c.c -o mempool_c.o

test_c: mempool_c.o mempooltest_c.o
	${CC} ${LDFLAGS} mempooltest_c.o mempool_c.o -o test_c

benchmark: mempool_c.o benchmark.o
	${CC} ${LDFLAGS} benchmark.o mempool_c.o -o benchmark


clean:
	${RM} *.o
	${RM} test_c

# not working on yosemite
valgrind: test_c
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
	--num-callers=20 --track-fds=yes --dsymutil=yes ./test_c
