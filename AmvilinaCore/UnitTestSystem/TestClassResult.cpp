#include "TestClassResult.hpp"

using namespace UnitTests;

void TestClassResult::AddMethodResult(const TestMethodResult& methodResult) {
    _methodsResults.push_back(methodResult);
    if(methodResult.IsSuccess())
        ++_successfulCount;
    _bytesLeaked += methodResult.bytesLeaked;
    _timeElapsed += methodResult.timeElapsed;
}

const std::vector<TestMethodResult> TestClassResult::GetMethodsResults() const {
    return _methodsResults;
}

u64 TestClassResult::SuccessfulCount() const {
    return _successfulCount;
}

u64 TestClassResult::AllCount() const {
    return _methodsResults.size();
}

u64 TestClassResult::BytesLeaked() const {
    return _bytesLeaked;
}

u64 TestClassResult::TimeElapsed() const {
    return _timeElapsed;
}
