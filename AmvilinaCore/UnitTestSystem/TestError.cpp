#include "TestError.hpp"

namespace UnitTests
{

TestError::TestError(){}

TestError::TestError(u64 line, const std::string& code, const std::string& extraMessage)
:
line {line},
code {code},
extraMessage {extraMessage}
{}

bool operator==(const TestError& a, const TestError& b) {
    return a.line == b.line &&
    a.code == b.code &&
    a.extraMessage == b.extraMessage;
}

}
