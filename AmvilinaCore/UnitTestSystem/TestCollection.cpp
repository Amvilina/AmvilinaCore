#include "TestCollection.hpp"
#include <iostream>

using namespace UnitTests;

TestCollection& TestCollection::Instance() {
    static TestCollection testCollection;
    return testCollection;
}

void TestCollection::AddTest(TestClass* test) {
    _testPointers.push_back(test);
}

void TestCollection::RunAndPrintAll() const{
    RunAndPrint(PrintType::All);
}

void TestCollection::RunAndPrintFailed() const{
    RunAndPrint(PrintType::Failed);
}

void TestCollection::RunAndPrintTime() const{
    RunAndPrint(PrintType::Time);
}

void TestCollection::RunAndPrintInteresting() const{
    RunAndPrint(PrintType::Interesting);
}

void TestCollection::RunAndPrint(PrintType printType) const{
    for (auto testPointer : _testPointers) {
        std::cout << testPointer->Name() << ' ';
        TestClassResult result = testPointer->Run();
        PrintHeader(result);
        for (TestMethodResult methodResult : result.GetMethodsResults())
            if(ShouldPrintMethodResult(methodResult, printType))
                std::cout << methodResult.GetMessage();
        std::cout << "===============================\n\n";
    }
}

void TestCollection::PrintHeader(const TestClassResult& result) const {
    std::cout << "( " << result.SuccessfulCount() << " / " << result.AllCount() << " )"
              << " in " << (double)result.TimeElapsed() / 1000.0 << "ms with " << result.BytesLeaked() << " bytes leaked\n";
    std::cout << "===============================\n";
}

bool TestCollection::ShouldPrintMethodResult(const TestMethodResult& result, PrintType printType) const{
    if(printType == PrintType::Failed)
        return !result.IsSuccess();
    
    if(printType == PrintType::Time)
        return result.IsTimeChecking();
    
    if(printType == PrintType::Interesting)
        return !result.IsSuccess() || result.IsTimeChecking();
    
    return true;
}
