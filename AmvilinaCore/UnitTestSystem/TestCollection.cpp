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

void TestCollection::RunAndPrintMemory() const{
    RunAndPrint(PrintType::Memory);
}

void TestCollection::RunAndPrint(PrintType printType) const{
    for (auto testPointer : _testPointers) {
        std::cout << testPointer->Name() << ' ';
        TestClassResult result = testPointer->Run();
        PrintHeader(result);
        for (TestMethodResult methodResult : result.GetMethodsResults())
            switch (printType) {
                case PrintType::All:
                    std::cout << methodResult.GetMessage();
                    break;
                case PrintType::Failed:
                    if(!methodResult.IsSuccess())
                        std::cout << methodResult.GetMessage();
                    break;
                case PrintType::Time:
                    if(methodResult.IsTimeChecking())
                        std::cout << methodResult.GetMessage();
                    break;
                case PrintType::Memory:
                    if(methodResult.IsMemoryChecking())
                        std::cout << methodResult.GetMessage();
                    break;
            }
        std::cout << "===============================\n\n";
    }
}

void TestCollection::PrintHeader(const TestClassResult& result) const {
    std::cout << "( " << result.SuccessfulCount() << " / " << result.AllCount() << " )"
              << " in " << result.TimeElapsed() << " microseconds with " << result.BytesLeaked() << " bytes leaked\n";
    std::cout << "===============================\n";
}
