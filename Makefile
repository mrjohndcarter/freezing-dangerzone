CFLAGS=-Wall -pedantic -g
CXXFLAGS=-Wall -pedantic -g
PACKAGE_LIB_DIR=/Users/jcarter/Development/freezing-dangerzone

# CPP Unit paths
CPP_UNIT_INCLUDE=/usr/local/Cellar/cppunit/1.12.1/include/cppunit
CPP_UNIT_LIB=/usr/local/Cellar/cppunit/1.12.1/lib

all: lib test_c test_cpp auto_tests

lib: mempool_c.o mempool_cpp.o
	${AR} ${ARFLAGS} libmempool.a mempool_c.o mempool_cpp.o

mempool_c.o: mempool_c.h mempool_c.c
	${CC} ${CFLAGS} -c mempool_c.c -o mempool_c.o

mempool_cpp.o: mempool_cpp.h mempool_cpp.cpp
	${CXX} ${CFLAGS} -c mempool_cpp.cpp -o mempool_cpp.o

test_c: mempooltest_c.o
	${CC} ${LDFLAGS} -L${PACKAGE_LIB_DIR} -lmempool mempooltest_c.o -o test_c

test_cpp: mempooltest_cpp.o
	${CXX} ${LDFLAGS} -L${PACKAGE_LIB_DIR} -lmempool mempooltest_cpp.o -o test_cpp

mempooltest_c.o: mempooltest_c.c
	${CC} ${CFLAGS} -c mempooltest_c.c -o mempooltest_c.o

mempooltest_cpp.o: mempooltest_cpp.cpp
	${CXX} ${CXXFLAGS} -c mempooltest_cpp.cpp -o mempooltest_cpp.o

clean:
	${RM} *.o
	${RM} *.a
	${RM} test_c
	${RM} test_cpp

# not working on yosemite
valgrind: test_c
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
	--num-callers=20 --track-fds=yes --dsymutil=yes ./test_c

auto_tests: auto_tests.o lib
	${CXX} ${LDFLAGS} -L${PACKAGE_LIB_DIR} -L${CPP_UNIT_LIB} -lmempool -lcppunit auto_tests.o -o auto_tests

auto_tests.o: auto_tests.cpp
	${CXX} ${CFLAGS} -I${CPP_UNIT_INCLUDE} -c auto_tests.cpp -o auto_tests.o
