#ifndef TestClassResult_hpp
#define TestClassResult_hpp

#include <vector>
#include "TestMethodResult.hpp"

namespace UnitTests {

class TestClassResult{
private:
    std::vector<TestMethodResult> _methodsResults;
    u64 _successfulCount = 0;
    u64 _bytesLeaked = 0;
    u64 _timeElapsed = 0;
public:
    void AddMethodResult(const TestMethodResult& methodResult);
    const std::vector<TestMethodResult> GetMethodsResults() const;
    u64 SuccessfulCount() const;
    u64 AllCount() const;
    u64 BytesLeaked() const;
    u64 TimeElapsed() const;
};

}

#endif
