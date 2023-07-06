#include "TestAllocator.hpp"
#include <stdlib.h>

using namespace UnitTests;

u64 TestAllocatorBytesCounter::_bytes = 0;

void TestAllocatorBytesCounter::Add(u64 bytes) {
    _bytes += bytes;
}

void TestAllocatorBytesCounter::Remove(u64 bytes) {
    _bytes -= bytes;
}

void TestAllocatorBytesCounter::Reset() {
    _bytes = 0;
}

u64 TestAllocatorBytesCounter::Get() {
    return _bytes;
}

void * operator new(size_t n)
{
    void* ptr = malloc(n + sizeof(n));
    size_t* dataPtr = (size_t*)ptr;
    dataPtr[0] = n;
    ptr = (void*)(++dataPtr);
    TestAllocatorBytesCounter::Add(n);
    return ptr;
}

void operator delete(void * ptr) throw()
{
    size_t* dataPtr = (size_t*)ptr;
    --dataPtr;
    size_t n = *dataPtr;
    ptr = (void*)(dataPtr);
    TestAllocatorBytesCounter::Remove(n);
    free(ptr);
}
