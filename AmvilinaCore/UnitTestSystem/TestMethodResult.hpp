#ifndef TestMethodResult_hpp
#define TestMethodResult_hpp

#include "TestError.hpp"

namespace UnitTests{

class TestMethodResult{
public:
    std::string methodName;
    TestError error;
    u64 timeElapsed = 0;
    u64 bytesLeaked = 0;
public:
    TestMethodResult(const std::string& methodName);
    std::string GetMessage() const;
    bool IsMemoryLeak() const;
    bool IsSuccess() const;
};

}
#endif
