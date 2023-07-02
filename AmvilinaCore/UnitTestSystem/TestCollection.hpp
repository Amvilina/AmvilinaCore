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
    void RunAndPrintMemory() const;
    void RunAndPrintTime() const;
private:
    enum class PrintType {
        All,
        Failed,
        Memory,
        Time
    };
    void RunAndPrint(PrintType printType) const;
    void PrintHeader(const TestClassResult& result) const;
};

}
#endif
