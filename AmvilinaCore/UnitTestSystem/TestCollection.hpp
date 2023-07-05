#ifndef TestCollection_hpp
#define TestCollection_hpp

#include <vector>
#include "TestClass.hpp"

namespace UnitTests{

class TestClass;

class TestCollection{
private:
    TestCollection() {}
    std::vector<TestClass*> _testPointers;
public:
    static TestCollection& Instance();
    void AddTest(TestClass* test);
    void RunAndPrintAll() const;
    void RunAndPrintFailed() const;
    void RunAndPrintTime() const;
    void RunAndPrintInteresting() const;
private:
    enum class PrintType {
        All,
        Failed,
        Time,
        Interesting
    };
    void RunAndPrint(PrintType printType) const;
    void PrintHeader(const TestClassResult& result) const;
    bool ShouldPrintMethodResult(const TestMethodResult& result, PrintType printType) const;
};

}
#endif
