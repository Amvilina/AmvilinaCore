#include "TestAllocator.hpp"

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
