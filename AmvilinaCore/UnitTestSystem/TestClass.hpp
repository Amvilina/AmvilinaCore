#ifndef BaseTest_hpp
#define BaseTest_hpp

#include "TestClassResult.hpp"
#include "Timer.hpp"
#include "TestAllocator.hpp"
#include "Assert.hpp"

namespace UnitTests {

class TestClass{
private:
    std::string _name;
public:
    TestClass(const std::string name);
    std::string Name() const;
    virtual TestClassResult Run() = 0;
};

std::string MustBeCloseDoublesExtraInfo(double a, double b);

}


#define TEST_CLASS_BEGIN(name)                                                          \
class name : public UnitTests::TestClass {                                              \
public:                                                                                 \
    name() : TestClass(#name) { }                                                       \
    UnitTests::TestClassResult Run() override {                                         \
        using namespace UnitTests;                                                      \
        TestClassResult classResult;                                                    \
        TEST_METHOD_START("Validation"){}                                               \
                                             
#define TEST_METHOD_START(name)                                                         \
        {                                                                               \
            TestMethodResult methodResult(name);                                        \
            Timer timer;                                                                \
            TestAllocatorBytesCounter::Reset();                                         \
            try                                                                         \

//user test methods
#define TEST_METHOD(name)   \
TEST_METHOD_END             \
TEST_METHOD_START(#name)    \

#define TEST_METHOD_END                                                                 \
            catch(const TestError& error) {                                             \
                methodResult.error = error;                                             \
            }                                                                           \
            methodResult.bytesLeaked = TestAllocatorBytesCounter::Get();                \
            methodResult.timeElapsed = timer.Elapsed();                                 \
            classResult.AddMethodResult(methodResult);                                  \
        }                                                                               \
            
#define TEST_CLASS_END(name)                                                            \
        TEST_METHOD_END                                                                 \
        return classResult;                                                             \
    }                                                                                   \
};                                                                                      \
namespace {                                                                             \
static name name##Instance;                                                             \
}                                                                                       \

#define TIME_CHECKING methodResult.isTimeChecking = true

#define MEMORY_CHECKING methodResult.isMemoryChecking = true
        
#define MUST_BE_TRUE(exp) if(!(exp)) throw(TestError(__LINE__, #exp, "Expected True but was False"))

#define MUST_BE_FALSE(exp) if(exp) throw(TestError(__LINE__, #exp, "Expected False but was True"))

#define MUST_BE_CLOSE_DOUBLES(a, b)                                         \
if( (((a) > (b)) ? ((a) - (b)) : ((b) - (a))) > 1e-9 )                      \
throw( TestError( __LINE__,                                                 \
                  std::string(#a) + std::string(" == ") + std::string(#b),  \
                  MustBeCloseDoublesExtraInfo((a),(b)) ) )

#define MUST_THROW_EXCEPTION_PARAMS(exceptionClass, code, extraInfo, ...)   \
try {                                                                       \
    __VA_ARGS__;                                                            \
throw(TestError(__LINE__, code, #extraInfo));                               \
}                                                                           \
catch(const TestError& e) {throw;}                                          \
catch(const exceptionClass& e) { }                                          \
catch(...){ throw(TestError(__LINE__, code, #extraInfo));}';'               \
//This ';' is to force user to write MUST_THROW_EXCEPTION(...); <- with semicolon at the end

#define MUST_THROW_EXCEPTION(exceptionClass, ...) \
MUST_THROW_EXCEPTION_PARAMS(exceptionClass, #__VA_ARGS__, There were no exceptions of type #exceptionClass  , __VA_ARGS__)

#define MUST_ASSERT(...) \
MUST_THROW_EXCEPTION_PARAMS(AssertException, #__VA_ARGS__, There were no ASSERTs, __VA_ARGS__)

#endif
