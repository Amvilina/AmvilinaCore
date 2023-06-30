#ifndef TestCollection_hpp
#define TestCollection_hpp

#include <vector>

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
    void RunAndPrintInteresting() const;
private:
    void RunAndPrint(bool onlyInteresting) const;
};

}
#endif
