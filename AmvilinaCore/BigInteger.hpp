#ifndef BigInteger_hpp
#define BigInteger_hpp

#include <iostream>

#include <vector>
#include <string>
#include "IntTypes.hpp"

namespace AmvilinaCore{

class BigInteger {
private:
    // LITTLE ENDIAN
    std::vector<u64> _chunks;
    bool _sign = true;
public:
    BigInteger();
    BigInteger( u8  a );
    BigInteger( i8  a );
    BigInteger( u16 a );
    BigInteger( i16 a );
    BigInteger( u32 a );
    BigInteger( i32 a );
    BigInteger( u64 a );
    BigInteger( i64 a );
    BigInteger( const char* number );
    BigInteger( const std::string& number );
    BigInteger( const BigInteger& other )            = default;
    BigInteger( BigInteger&& other )                 = default;
    BigInteger& operator=( const BigInteger& other ) = default;
    BigInteger& operator=( BigInteger&& other )      = default;
    
    static BigInteger CreateWithNChunks(u64 N);
    static BigInteger CreateFromBinaryString(const std::string& string);
    static BigInteger CreateFromDecimalString(const std::string& string);
    static BigInteger CreateFromHexString(const std::string& string);
    
    u64 NChunks() const;
    const u64& ChunkAt(u64 index) const;
    u64& ChunkAt(u64 index);
    bool Sign() const;
    
    enum ComparisonResult{Less = -1, Equal = 0, Greater = 1};
    ComparisonResult CompareWith(const BigInteger& other) const;
    static ComparisonResult Compare(const BigInteger& first, const BigInteger& second);
    friend bool operator==( const BigInteger& first, const BigInteger& second );
    friend bool operator!=( const BigInteger& first, const BigInteger& second );
    friend bool operator> ( const BigInteger& first, const BigInteger& second );
    friend bool operator>=( const BigInteger& first, const BigInteger& second );
    friend bool operator< ( const BigInteger& first, const BigInteger& second );
    friend bool operator<=( const BigInteger& first, const BigInteger& second );
    
    BigInteger operator+() const;
    BigInteger operator-() const;
    friend BigInteger operator+(const BigInteger& first, const BigInteger& second);
    friend BigInteger operator-(const BigInteger& first, const BigInteger& second);
    friend BigInteger operator*(const BigInteger& first, const BigInteger& second);
    friend BigInteger operator/(const BigInteger& first, const BigInteger& second);
    friend BigInteger operator%(const BigInteger& first, const BigInteger& second);
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
    struct DivisionResult;
    static DivisionResult Divide(const BigInteger& dividend, const BigInteger& divisor);
    DivisionResult Divide(const BigInteger& other) const;
    BigInteger Mod(const BigInteger& other) const;
    
    bool IsOdd() const;
    bool IsEven() const;
    static bool IsOdd(const BigInteger& a);
    static bool IsEven(const BigInteger& a);
    
    static BigInteger Power(const BigInteger& base, const BigInteger& power);
    BigInteger ToPower(const BigInteger& power) const;
    
    BigInteger  operator>> ( u8 count ) const;
    BigInteger& operator>>=( u8 count );
    BigInteger  operator<< ( u8 count ) const;
    BigInteger& operator<<=( u8 count );
    friend BigInteger  operator&  ( const BigInteger& first, const BigInteger& second);
    friend BigInteger  operator|  ( const BigInteger& first, const BigInteger& second);
    friend BigInteger  operator^  ( const BigInteger& first, const BigInteger& second);
    BigInteger& operator&= ( const BigInteger& other);
    BigInteger& operator|= ( const BigInteger& other);
    BigInteger& operator^= ( const BigInteger& other);
    BigInteger  operator~  () const;
    
    std::vector<bool> GetBinaryVector() const;
    std::vector<char> GetBinaryCharVector() const;
    std::vector<char> GetDecimalVector() const;
    std::vector<char> GetHexVector() const;
    
    std::string ToBinaryString() const;
    std::string ToDecimalString() const;
    std::string ToHexString() const;
    
    void PrintBinary() const;
    void PrintDecimal() const;
    void PrintHex() const;
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& a);
private:
    static BigInteger CreateFromString(u8 base, const std::string& string);
    void DeleteZeroChunks();
    static u64 NChunksForNDigits(u8 base, u64 nDigits);
    
    enum class Function {
        Xor,
        And,
        Or,
        Add,
        Subtract
    };
    static BigInteger ApplyFunctionWithoutSign(Function function, const BigInteger& first, const BigInteger& second);
    
    std::string GetStringRepresentation( u8 base ) const;
    std::vector<char> GetVectorCharRepresentation( u8 base ) const;
    std::vector<char> GetVectorCharDecimalRepresentation() const;
};

struct BigInteger::DivisionResult {
    BigInteger div;
    BigInteger mod;
};


}
#endif
