#include <Test.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <TestResult.h>
#include <TextTestRunner.h>
#include <TestAssert.h>
#include <TestCaller.h>

#include "mempool_cpp.h"

class MemoryPoolTest : public CppUnit::TestFixture
{
private:
    MEMPOOL_CPP::MemoryPool *poolDefault;
public:
    void setUp() {

    }
    void tearDown() {

    }
    void testDefaultInstantiation() {
        char *aString;
        poolDefault = new MEMPOOL_CPP::MemoryPool();
        CPPUNIT_ASSERT_NO_THROW(aString = (char *)poolDefault->allocate(sizeof(char) * 30));
        CPPUNIT_ASSERT(aString != NULL);
    }

};

int main(void) {
    CppUnit::TextTestRunner testRunner;
    testRunner.addTest(new CppUnit::TestCaller<MemoryPoolTest>("testDefaultInstantiation", &MemoryPoolTest::testDefaultInstantiation));
    testRunner.run();
    return 0;
}
