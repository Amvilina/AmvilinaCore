#include "String.hpp"
#include "Assert.hpp"
#include "BitChunk.hpp"

using namespace AmvilinaCore;


bool String::IsValidDigit(u8 base, char c) {
    if(base == 2)
        return IsBinaryDigit(c);
    if(base == 10)
        return IsDecimalDigit(c);
    if(base == 16)
        return IsHexDigit(c);
    ASSERT(false);
    return false;
}

bool String::IsBinaryDigit(char c) {
    return (c == '0') || (c == '1');
}

bool String::IsDecimalDigit(char c) {
    return IsDigit(c);
}

bool String::IsDigit(char c) {
    return ((c - '0') >= 0) && ((c - '0') <= 9);
}

bool String::IsHexDigit(char c) {
    return IsDigit(c) || IsHexLetter(c);
}

bool String::IsHexLetter(char c) {
    c = ToLower(c);
    return ((c - 'a') >= 0) && ((c - 'a') <= 5);
}

char String::ToLower(char c) {
    if (c >= 'A' && c <= 'Z')
        c = c + ('a' - 'A');
    return c;
}

bool String::IsLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

u8 String::DigitValue(u8 base, char c) {
    ASSERT(IsValidDigit(base, c));
    if(base == 10)
        return c - '0';
    if(base == 2)
        return c - '0';
    if(base == 16)
        return HexValueForDigit(c);
    ASSERT(false);
    return 0;
}

u8 String::HexValueForDigit(char c) {
    ASSERT(IsHexDigit(c));
    if(IsDigit(c))
        return c - '0';
    
    c = ToLower(c);
    return (c - 'a') + 10;
}

char String::GetCharFromValue(u8 base, u8 value) {
    if(base == 2)
        return GetCharFromBinaryValue(value);
    if(base == 10)
        return GetCharFromDecimalValue(value);
    if(base == 16)
        return GetCharFromHexValue(value);
    ASSERT(false);
    return 0;
}

char String::GetCharFromBinaryValue(u8 value) {
    ASSERT(value >= 0 && value <= 1);
    return value + '0';
}

char String::GetCharFromDecimalValue(u8 value) {
    ASSERT(value >= 0 && value <= 9);
    return value + '0';
}

char String::GetCharFromHexValue(u8 value) {
    ASSERT(value >= 0 && value <= 15);
    if(value <= 9)
        return '0' + value;
    return 'A' + (value - 10);
}

bool String::IsValidPrefix(u8 base, const std::string& c) {
    return c == GetPrefixForBase(base);
}

std::string String::GetPrefixForBase(u8 base) {
    if(base == 2)
        return "0b";
    if(base == 10)
        return "";
    if(base == 16)
        return "0x";
    ASSERT(false);
    return "";
}

u8 String::GetPrefixLengthForBase(u8 base) {
    return GetPrefixForBase(base).length();
}

bool String::IsValidNumber(u8 base, const std::string& string) {
    ASSERT(base == 2 || base == 10 || base == 16);
    if(string.length() == 0)
        return false;
    
    const u8 minusOffset = (string[0] == '-') ? 1 : 0;
    const u8 prefixLength = GetPrefixLengthForBase(base);
    const u8 offset = minusOffset + prefixLength;
    
    if(string.length() <= offset)
        return false;
    
    if(!IsValidPrefix(base, string.substr(minusOffset, prefixLength)))
        return false;
    
    auto it = string.begin() + offset;
    auto end = string.end();
    
    while(it != end) {
        if(!IsValidDigit(base, *it))
            return false;
        ++it;
    }
    
    return true;
};

bool String::IsValidBinaryString(const std::string& number) {
    return IsValidNumber(2, number);
}

bool String::IsValidDecimalString(const std::string& number) {
    return IsValidNumber(10, number);
}

bool String::IsValidHexString(const std::string& number) {
    return IsValidNumber(16, number);
}

std::vector<char> String::GetCharVectorFromChunk( u8 base, u64 chunk ) {
    std::vector<char> result (BitChunk::NDigitsInChunkBase(base));
    auto it = result.rbegin();
    auto end = result.rend();
    while(it != end) {
        *it = GetCharFromValue(base, chunk % base);
        chunk /= base;
        ++it;
    }
    return result;
}
