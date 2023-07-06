#ifndef BitChunkTests_hpp
#define BitChunkTests_hpp

#include "TestClass.hpp"
#include "BitChunk.hpp"

namespace BitChunkTests {

using namespace AmvilinaCore;

TEST_CLASS_BEGIN(BitChunkTest)

TEST_METHOD(NDigitsInChunkBase)
{
    MUST_BE_TRUE(BitChunk::NDigitsInChunkBase(2) == 64);
    MUST_BE_TRUE(BitChunk::NDigitsInChunkBase(10) == 18);
    MUST_BE_TRUE(BitChunk::NDigitsInChunkBase(16) == 16);
}

TEST_METHOD(NDigitsInChunkBase_Wrong_Base_Assert)
{
    MUST_ASSERT(BitChunk::NDigitsInChunkBase(0));
    MUST_ASSERT(BitChunk::NDigitsInChunkBase(1));
    MUST_ASSERT(BitChunk::NDigitsInChunkBase(5));
    MUST_ASSERT(BitChunk::NDigitsInChunkBase(18));
}

TEST_METHOD(GetBitAtIndex)
{
    u64 chunk = 0b10100101;
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 0) == true);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 1) == false);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 2) == true);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 3) == false);
    
    u64 one = u64(1) << 63;
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(one, 63) == true);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(one, 62) == false);

}

TEST_METHOD(GetBitAtIndex_Out_Of_Range_Index_Assert)
{
    MUST_ASSERT(BitChunk::GetBitAtIndex(0, 64));
    MUST_ASSERT(BitChunk::GetBitAtIndex(0, 68));
    MUST_ASSERT(BitChunk::GetBitAtIndex(0, 72));
}

TEST_METHOD(SetBitAtIndex)
{
    u64 chunk = 0b111010;
    BitChunk::SetBitAtIndex(chunk, 0, true);
    BitChunk::SetBitAtIndex(chunk, 1, false);
    BitChunk::SetBitAtIndex(chunk, 2, false);
    BitChunk::SetBitAtIndex(chunk, 3, true);
    BitChunk::SetBitAtIndex(chunk, 4, false);
    
    MUST_BE_TRUE(chunk == 0b101001);
    
    BitChunk::SetBitAtIndex(chunk, 63, true);
    BitChunk::SetBitAtIndex(chunk, 62, false);
    
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 63) == true);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 62) == false);
}

TEST_METHOD(SetBitAtIndex_Out_Of_Range_Index_Assert)
{
    u64 chunk;
    MUST_ASSERT(BitChunk::SetBitAtIndex(chunk, 64, true));
    MUST_ASSERT(BitChunk::SetBitAtIndex(chunk, 65, true));
    MUST_ASSERT(BitChunk::SetBitAtIndex(chunk, 102, true));
}

TEST_METHOD(GetChunkFromDigits)
{
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(2, "0b10101010101", 6, 8) == 0b101);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(2, "1101110101", 0, 5) == 0b110111);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(2, "JJ1011110100", 7, 11) == 0b10100);
    
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(10, "159212", 0, 5) == 159212);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(10, "AAA192402", 6, 8) == 402);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(10, "333333XXXXX", 0, 3) == 3333);
    
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(16, "159212", 0, 5) == 0x159212);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(16, "AfD192402", 0, 4) == 0xAFD19);
    MUST_BE_TRUE(BitChunk::GetChunkFromDigits(16, "---fBc1D6", 5, 8) == 0xC1D6);
}

TEST_METHOD(GetChunkFromDigits_Wrong_Base_Assert)
{
    MUST_ASSERT(BitChunk::GetChunkFromDigits(0, "10100101010", 1, 2));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(1, "10100101010", 1, 2));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(13, "10100101010", 1, 2));
}

TEST_METHOD(GetChunkFromDigits_Not_Valid_Position_Assert)
{
    MUST_ASSERT(BitChunk::GetChunkFromDigits(10, "0123456789", 0, 10));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(10, "0123456789", 5, 4));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(10, "0123456789", 12, 15));
}

TEST_METHOD(GetChunkFromDigits_Too_Big_Number_Assert)
{
    MUST_ASSERT(BitChunk::GetChunkFromDigits(2, std::string(100, '1'), 0, 64));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(10, "8279512576128795126512598752151209827512", 0, 20));
    MUST_ASSERT(BitChunk::GetChunkFromDigits(16, "175189251259818998ffaddf93851", 0, 20));
}

TEST_METHOD(ShiftChunkRightAndReturnCarryBit)
{
    u64 chunk = 0b10101011;
    bool carry = BitChunk::ShiftChunkRightAndReturnCarryBit(chunk, false);
    
    MUST_BE_TRUE(chunk == 0b1010101);
    MUST_BE_TRUE(carry = true);
    
    carry = BitChunk::ShiftChunkRightAndReturnCarryBit(chunk, false);
    MUST_BE_TRUE(chunk == 0b101010);
    MUST_BE_TRUE(carry == true);
    
    carry = BitChunk::ShiftChunkRightAndReturnCarryBit(chunk, false);
    
    MUST_BE_TRUE(chunk == 0b10101);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::ShiftChunkRightAndReturnCarryBit(chunk, true);
    MUST_BE_TRUE(BitChunk::GetBitAtIndex(chunk, 63) == true);
    MUST_BE_TRUE(carry == true);
}

TEST_METHOD(ShiftChunkLeftAndReturnCarryBit)
{
    u64 chunk = 0b101101;
    bool carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, false);
    
    MUST_BE_TRUE(chunk == 0b1011010);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, true);
    
    MUST_BE_TRUE(chunk == 0b10110101);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, true);
    
    MUST_BE_TRUE(chunk == 0b101101011);
    MUST_BE_TRUE(carry == false);
    
    BitChunk::SetBitAtIndex(chunk, 63, true);
    carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, true);
    
    MUST_BE_TRUE(chunk == 0b1011010111);
    MUST_BE_TRUE(carry == true);
    
    carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, false);
    
    MUST_BE_TRUE(chunk == 0b10110101110);
    MUST_BE_TRUE(carry == false);
}

TEST_METHOD(AddChunksAndReturnCarryBit)
{
    u64 a = 25125;
    u64 b = 89241982;
    u64 copy = a;
    bool carry = BitChunk::AddChunksAndReturnCarryBit(a, b, true);
    
    MUST_BE_TRUE(a == copy + b + 1);
    MUST_BE_TRUE(carry == false);
    
    u64 max = BitChunk::MAX_VALUE;
    carry = BitChunk::AddChunksAndReturnCarryBit(max, 1, false);
    
    MUST_BE_TRUE(max == 0);
    MUST_BE_TRUE(carry == true);
}

TEST_METHOD(SubtractChunksAndReturnIfBorrow)
{
    u64 a = 1252151;
    bool carry = BitChunk::SubtractChunksAndReturnIfBorrow(a, 51, false);
    
    MUST_BE_TRUE(a == 1252100);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::SubtractChunksAndReturnIfBorrow(a, 0, true);
    
    MUST_BE_TRUE(a == 1252099);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::SubtractChunksAndReturnIfBorrow(a, a, false);
    
    MUST_BE_TRUE(a == 0);
    MUST_BE_TRUE(carry == false);
    
    carry = BitChunk::SubtractChunksAndReturnIfBorrow(a, 4, true);
    
    MUST_BE_TRUE(a == BitChunk::MAX_VALUE - 4);
    MUST_BE_TRUE(carry == true);
    
    u64 b = 1242;
    carry = BitChunk::SubtractChunksAndReturnIfBorrow(b, 1243, false);
    
    MUST_BE_TRUE(b == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(carry == true);
}

TEST_CLASS_END(BitChunkTest)

}
#endif
