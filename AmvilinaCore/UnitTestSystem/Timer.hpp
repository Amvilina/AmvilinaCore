#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

namespace UnitTests {

using namespace std::chrono;

using u64 = uint64_t;

class Timer{
private:
    time_point<high_resolution_clock> _lastTimePoint;
public:
    Timer();
    void Restart();
    u64 Elapsed();
};

}

#endif
