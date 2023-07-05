#include "UnitTests.hpp"

int main(int argc, const char * argv[]) {
    UnitTests::Run();
    return 0;
}

//#ifndef String_hpp
//#define String_hpp
//
//#include "Array.hpp"
//
//namespace Core{
//
//template <class Allocator = std::allocator<char>>
//class String : public Array<char, Allocator>{
//public:
//    String();
//    String(const char* str);
////    String(const String& other);
////    String(String&& other);
////    String& operator=(const String& other);
////    String& operator=(String&& other);
//
//    char* CString();
//    const char* CString() const;
//    u64 Length() const;
//
//    friend String operator+(const String& first, char c);
//    friend String operator+(char c, const String& first);
//    friend String operator+(const String& first, const String& second);
//    String& operator+=(char c);
//    String& operator+=(const String& other);
//};
//
//}
//#endif

//#include "String.hpp"
//
//using namespace Core;
//
//#define STRING_TEMPLATE template <class Allocator>
//#define STRING_CLASS String<Allocator>
//
////STRING_TEMPLATE
////STRING_CLASS::String() : Array<char, Allocator>() {}
//
////STRING_TEMPLATE
////STRING_CLASS::String(const char* str) : Array<char, Allocator>(strlen(str)) {
////    char* thisPtr = &_data[0];
////    while(*str != '\0') {
////        *thisPtr = *str;
////        ++str;
////        ++thisPtr;
////    }
////}
//
////STRING_TEMPLATE
////String::String(const String& other) : Array<char, Al>
////
////STRING_TEMPLATE
////STRING_CLASS::String(String&& other);
////
////STRING_TEMPLATE
////STRING_CLASS& STRING_CLASS::operator=(const String& other);
////
////STRING_TEMPLATE
////STRING_CLASS& STRING_CLASS::operator=(String&& other);
////
////STRING_TEMPLATE
////char* STRING_CLASS::CString();
////
////STRING_TEMPLATE
////const char* STRING_CLASS::CString() const;
////
////STRING_TEMPLATE
////u64 STRING_CLASS::Length() const;
////
////STRING_TEMPLATE
////STRING_CLASS operator+(const STRING_CLASS& first, char c);
////
////STRING_TEMPLATE
////STRING_CLASS operator+(char c, const STRING_CLASS& first);
////
////STRING_TEMPLATE
////STRING_CLASS operator+(const STRING_CLASS& first, const STRING_CLASS& second);
////
////STRING_TEMPLATE
////STRING_CLASS& STRING_CLASS::operator+=(char c);
////
////STRING_TEMPLATE
////STRING_CLASS& STRING_CLASS::operator+=(const String& other);


//#ifndef BigInteger_hpp
//#define BigInteger_hpp
//
//#include "Array.hpp"
//#include <string>
//
//namespace Core{
//
//class BigInteger{
//private:
//    // Little Endian
//    Array<u64> _chunks;
//    static constexpr u8 BITS_IN_CHUNK = 64;
//    bool _sign = true;
//public:
//    BigInteger();
//    BigInteger( u8  a );
//    BigInteger( i8  a );
//    BigInteger( u16 a );
//    BigInteger( i16 a );
//    BigInteger( u32 a );
//    BigInteger( i32 a );
//    BigInteger( u64 a );
//    BigInteger( i64 a );
//    BigInteger( const std::string& number );
//    BigInteger( const BigInteger& other )            = default;
//    BigInteger( BigInteger&& other )                 = default;
//    BigInteger& operator=( const BigInteger& other ) = default;
//    BigInteger& operator=( BigInteger&& other )      = default;
//
//    static bool IsValidStringBase2(const std::string& number);
//
//    static BigInteger CreateBigIntegerFromStringBase2(const std::string& number);
//
//private:
//
//    static BigInteger CreateBigIntegerWithNumberOfChunks(u64 nChunks);
//    static u64 GetChunkFromBinaryDigits( const std::string& digits, u64 first, u64 last );
//    static u64 NumberOfChunksForNumberBinaryDigits(u64 nDigits);
//};
//
//}
//#endif

//auto a = BigInteger::CreateBigIntegerFromStringBase2("0b1111111111111111111111111111111111111111111111111111111111111111111");


//#include "BigInteger.hpp"
//
//using namespace Core;
//
//BigInteger::BigInteger()      : _chunks(1) { _chunks[0] = 0; }
//BigInteger::BigInteger(u8 a)  : _chunks(1) { _chunks[0] = a; }
//BigInteger::BigInteger(i8 a)  : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
//BigInteger::BigInteger(u16 a) : _chunks(1) { _chunks[0] = a; }
//BigInteger::BigInteger(i16 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
//BigInteger::BigInteger(u32 a) : _chunks(1) { _chunks[0] = a; }
//BigInteger::BigInteger(i32 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
//BigInteger::BigInteger(u64 a) : _chunks(1) { _chunks[0] = a; }
//BigInteger::BigInteger(i64 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
//
////TODO: Rewrite with iterators
//bool BigInteger::IsValidStringBase2(const std::string& number) {
//    if(number.length() <= 2)
//        return false;
//    if(number[0] != '0')
//        return false;
//    if(number[1] != 'b')
//        return false;
//    for (u64 i = 2; i < number.length(); ++i)
//        if(number[i] != '0' && number[i] != '1')
//            return false;
//    return true;
//}
//#include <iostream>
////TODO: Rewrite with iterators
//BigInteger BigInteger::CreateBigIntegerFromStringBase2( const std::string& number ) {
//    ASSERT(IsValidStringBase2(number));
//
//    const u8 digitsOffset = 2;
//    u64 nChunks = NumberOfChunksForNumberBinaryDigits(number.length() - digitsOffset);
//    BigInteger result = CreateBigIntegerWithNumberOfChunks(nChunks);
//    for(u64 i = 0; i < nChunks - 1; ++i) {
//        u64 firstDigitIndex = digitsOffset + i * BITS_IN_CHUNK;
//        u64 lastDigitIndex = firstDigitIndex + BITS_IN_CHUNK - 1;
//        result._chunks.Append( GetChunkFromBinaryDigits(number, firstDigitIndex, lastDigitIndex) );
//    }
//
//    u64 digitIndex = digitsOffset + (nChunks-1) * BITS_IN_CHUNK;
//    result._chunks.Append( GetChunkFromBinaryDigits(number, digitIndex, number.size()-1) );
//
//    for (u64 chunk : result._chunks) {
//        std::cout << chunk << " ";
//    }
//    std::cout << '\n';
//
//    return result;
//}
//
////TODO: Rewrite with iterators
//u64 BigInteger::GetChunkFromBinaryDigits( const std::string& digits, u64 first, u64 last ) {
//    ASSERT(last >= first);
//    ASSERT(last <= digits.length());
//    ASSERT(last - first + 1 <= BITS_IN_CHUNK);
//
//    u64 result = 0;
//
//    for (u64 i = first; i <= last; ++i) {
//        result *= 2;
//        result += (digits[i] == '1') ? 1 : 0;
//    }
//
//    return result;
//}
//
//BigInteger BigInteger::CreateBigIntegerWithNumberOfChunks(u64 nChunks) {
//    BigInteger a;
//    a._chunks = Array<u64>(0, nChunks);
//    return a;
//}
//
//u64 BigInteger::NumberOfChunksForNumberBinaryDigits(u64 nDigits) {
//    return nDigits / BITS_IN_CHUNK + ((nDigits % BITS_IN_CHUNK == 0) ? 0 : 1);
//}
