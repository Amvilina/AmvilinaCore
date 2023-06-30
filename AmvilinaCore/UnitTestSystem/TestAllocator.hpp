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



template <class T>
class TestAllocator {
public:
    using value_type = T;
    
    T* allocate(u64 n) {
        TestAllocatorBytesCounter::Add(n * sizeof(T));
        return new T[n];
    }
    
    void deallocate(T* pointer, u64 n) {
        delete [] pointer;
        TestAllocatorBytesCounter::Remove(n * sizeof(T));
    }
};



}

#endif
