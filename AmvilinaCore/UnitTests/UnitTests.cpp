#include "UnitTests.hpp"
#include "TestCollection.hpp"
#include "ArrayTests.hpp"
namespace UnitTests{

void Run() {
    TestCollection::Instance().RunAndPrintAll();
    //TestCollection::Instance().RunAndPrintInteresting();
}

}

