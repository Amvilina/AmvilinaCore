#include "TestMethodResult.hpp"
#include <sstream>

using namespace UnitTests;

TestMethodResult::TestMethodResult(const std::string& methodName)
:
methodName {methodName}
{}

std::string TestMethodResult::GetMessage() const {
    std::stringstream ss;
    ss << methodName;
    
    if(IsSuccess()) {
        ss << " PASSED! ";
        if(IsTimeChecking())
            ss << timeElapsed << " microseconds";
        ss << '\n';
        return ss.str();
    }
    
    if(IsMemoryLeak()) {
        ss << " MEMORY LEAK!  <--  " << bytesLeaked << " bytes leaked\n";
        return ss.str();
    }
    
    ss << " FAILED!" << " Line " << error.line << ": "
    << error.code << "  <--  " << error.extraMessage << '\n';
    return ss.str();
}

bool TestMethodResult::IsMemoryLeak() const {
    return bytesLeaked > 0;
}
           
bool TestMethodResult::IsSuccess() const {
    const TestError nonError;
    return (error == nonError) && !IsMemoryLeak();
}

bool TestMethodResult::IsTimeChecking() const {
    return isTimeChecking;
}
