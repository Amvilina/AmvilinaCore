#include "TestClass.hpp"
#include "TestCollection.hpp"

#include <sstream>

namespace UnitTests{

TestClass::TestClass(const std::string name)
:
_name{name}
{
    TestCollection::Instance().AddTest(this);
}

std::string TestClass::Name() const{
    return _name;
}

std::string MustBeCloseDoublesExtraInfo(double a, double b) {
    std::stringstream ss;
    ss << a << " != " << b;
    return ss.str();
}

}


