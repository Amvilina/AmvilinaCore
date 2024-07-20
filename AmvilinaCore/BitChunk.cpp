#include "BitChunk.hpp"
#include "Assert.hpp"
#include "String.hpp"

using namespace AmvilinaCore;

u8 BitChunk::NDigitsInChunkBase(u8 base) {
    if(base == 2)
        return BITS_IN_CHUNK;
    if(base == 10)
        return DECIMAL_BASE_N_DIGITS;
    if(base == 16)
        return BITS_IN_CHUNK / 4;
    
    ASSERT(false);
    return 0;
}

bool BitChunk::GetBitAtIndex(u64 chunk, u8 index) {
    ASSERT(index >= 0 && index <= BITS_IN_CHUNK-1);
    return ((chunk >> index) & 1) == 1;
}

void BitChunk::SetBitAtIndex(u64& chunk, u8 index, bool bit) {
    ASSERT(index >= 0 && index <= BITS_IN_CHUNK-1);
    u64 one = u64(1) << index;
    chunk &= ~one;
    if(bit)
        chunk |= one;
}

u64 BitChunk::GetChunkFromDigits( u8 base, const std::string& digits, u64 first, u64 last ) {
    ASSERT(last >= first);
    ASSERT(first >= 0);
    ASSERT(last <= digits.length());
    ASSERT(last - first + 1 <= NDigitsInChunkBase(base));
    
    u64 result = 0;
    
    auto it = digits.begin() + first;
    auto end = digits.begin() + last + 1;
    
    while(it != end) {
        result *= base;
        result += String::DigitValue(base, *it);
        ++it;
    }
    
    return result;
}

bool BitChunk::ShiftChunkRightAndReturnCarryBit(u64& chunk, bool carry) {
    bool digit = GetBitAtIndex(chunk, 0);
    chunk >>= 1;
    SetBitAtIndex(chunk, BITS_IN_CHUNK-1, carry);
    return digit;
}

bool BitChunk::ShiftChunkLeftAndReturnCarryBit(u64& chunk, bool carry) {
    bool digit = GetBitAtIndex(chunk, BITS_IN_CHUNK-1);
    chunk <<= 1;
    SetBitAtIndex(chunk, 0, carry);
    return digit;
}

bool BitChunk::AddChunksAndReturnCarryBit(u64& baseChunk, u64 otherChunk, bool carry) {
    u64 copy = baseChunk;
    baseChunk += otherChunk;
    bool newCarry = (baseChunk < copy || baseChunk < otherChunk);
    baseChunk += (carry) ? 1 : 0;
    if(baseChunk < copy || baseChunk < otherChunk)
        newCarry = true;
    return newCarry;
}

bool BitChunk::SubtractChunksAndReturnIfBorrow(u64& baseChunk, u64 otherChunk, bool isBorrow) {
    bool isBorrowing = false;
    if(baseChunk == 0)
        isBorrowing = (otherChunk != 0) || isBorrow;

    baseChunk -= (isBorrow ? 1 : 0);
    if( baseChunk < otherChunk ) {
        baseChunk = MAX_VALUE - otherChunk + 1 + baseChunk;
        isBorrowing = true;
    } else {
        baseChunk -= otherChunk;
    }
    
    return isBorrowing;
}
