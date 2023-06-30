#include "TestCollection.hpp"
#include "TestClass.hpp"
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
    RunAndPrint(false);
}

void TestCollection::RunAndPrintInteresting() const{
    RunAndPrint(true);
}

void TestCollection::RunAndPrint(bool onlyInteresting) const{
    for (auto testPointer : _testPointers) {
        std::cout << testPointer->Name() << ' ';
        TestClassResult result = testPointer->Run();
        std::cout << "( " << result.SuccessfulCount() << " / " << result.AllCount() << " )"
                  << " in " << result.TimeElapsed() << " microseconds with " << result.BytesLeaked() << " bytes leaked\n";
        std::cout << "===============================\n";
        for (TestMethodResult methodResult : result.GetMethodsResults())
            if(onlyInteresting && methodResult.IsSuccess() && !methodResult.IsMemoryLeak())
                continue;
            else
                std::cout << methodResult.GetMessage();
        std::cout << "===============================\n\n";
    }
}
