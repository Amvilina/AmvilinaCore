#include "Timer.hpp"

using namespace UnitTests;

Timer::Timer() {
    _lastTimePoint = high_resolution_clock::now();
}

void Timer::Restart() {
    _lastTimePoint = high_resolution_clock::now();
}

u64 Timer::Elapsed() {
    auto now = high_resolution_clock::now();
    u64 duration = duration_cast<microseconds>(now - _lastTimePoint).count();
    Restart();
    return duration;
}
