#ifndef TestError_hpp
#define TestError_hpp

#include <string>

namespace UnitTests {

using u64 = uint64_t;

class TestError {
public:
    u64 line = 0;
    std::string code;
    std::string extraMessage;

    TestError();
    TestError(u64 line, const std::string& code, const std::string& extraMessage);
};

bool operator==(const TestError& a, const TestError& b);

}
#endif
