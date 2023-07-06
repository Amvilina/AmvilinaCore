#ifndef TestAllocator_hpp
#define TestAllocator_hpp

#include <cstdint>

namespace UnitTests{

using u64 = uint64_t;

class TestAllocatorBytesCounter {
private:
    static u64 _bytes;
    TestAllocatorBytesCounter() {}
public:
    static void Add(u64 bytes);
    static void Remove(u64 bytes);
    static void Reset();
    static u64 Get();
};

}

#endif
