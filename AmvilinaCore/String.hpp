#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <vector>
#include <string>
#include "IntTypes.hpp"

namespace AmvilinaCore {

class String {
public:
    static bool IsValidDigit(u8 base, char c);
    static bool IsBinaryDigit(char c);
    static bool IsDecimalDigit(char c);
    static bool IsDigit(char c);
    static bool IsHexDigit(char c);
    static bool IsHexLetter(char c);
    static char ToLower(char c);
    static bool IsLetter(char c);
    
    static u8 DigitValue(u8 base, char c);
    static u8 HexValueForDigit(char c);
    
    static char GetCharFromValue(u8 base, u8 value);
    static char GetCharFromBinaryValue(u8 value);
    static char GetCharFromDecimalValue(u8 value);
    static char GetCharFromHexValue(u8 value);
    
    static bool IsValidPrefix(u8 base, const std::string& prefix);
    static std::string GetPrefixForBase(u8 base);
    static u8 GetPrefixLengthForBase(u8 base);
    
    static bool IsValidNumber(u8 base, const std::string& string);
    static bool IsValidBinaryString(const std::string& number);
    static bool IsValidDecimalString(const std::string& number);
    static bool IsValidHexString(const std::string& number);
    
    static std::vector<char> GetCharVectorFromChunk( u8 base, u64 chunk );
};

}
#endif
