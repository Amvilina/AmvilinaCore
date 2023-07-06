#ifndef BitChunkUtils_hpp
#define BitChunkUtils_hpp

#include "IntTypes.hpp"
#include <string>

namespace AmvilinaCore {

class BitChunk {
public:
    static constexpr u8 BITS_IN_CHUNK = 64;
    static constexpr u64 DECIMAL_BASE = 1e18;
    static constexpr u64 DECIMAL_BASE_N_DIGITS = 18;
    static constexpr u64 MAX_VALUE = -1;
    
    static u8 NDigitsInChunkBase(u8 base);
    
    static bool GetBitAtIndex(u64 chunk, u8 index);            // the indices are:
    static void SetBitAtIndex(u64& chunk, u8 index, bool bit); // 63 62 ... 1 0
    
    static u64 GetChunkFromDigits( u8 base, const std::string& digits, u64 first, u64 last );
    
    static bool ShiftChunkRightAndReturnCarryBit(u64& chunk, bool carry);
    static bool ShiftChunkLeftAndReturnCarryBit(u64& chunk, bool carry);
    static bool AddChunksAndReturnCarryBit(u64& baseChunk, u64 otherChunk, bool carry);
    static bool SubtractChunksAndReturnIfBorrow(u64& baseChunk, u64 otherChunk, bool isBorrow);
};


}
#endif
