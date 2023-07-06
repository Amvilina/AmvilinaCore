#include "BigInteger.hpp"
#include "Assert.hpp"
#include "String.hpp"
#include "BitChunk.hpp"

namespace AmvilinaCore {

BigInteger::BigInteger()      : _chunks(1) { _chunks[0] = 0; }
BigInteger::BigInteger(u8 a)  : _chunks(1) { _chunks[0] = a; }
BigInteger::BigInteger(i8 a)  : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
BigInteger::BigInteger(u16 a) : _chunks(1) { _chunks[0] = a; }
BigInteger::BigInteger(i16 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
BigInteger::BigInteger(u32 a) : _chunks(1) { _chunks[0] = a; }
BigInteger::BigInteger(i32 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }
BigInteger::BigInteger(u64 a) : _chunks(1) { _chunks[0] = a; }
BigInteger::BigInteger(i64 a) : _chunks(1) { _chunks[0] = std::abs(a); _sign = a >= 0; }

BigInteger::BigInteger( const char* number )
:
BigInteger(std::string(number))
{}

BigInteger::BigInteger( const std::string& number ) {
    if(String::IsValidBinaryString(number))
    {
        *this = CreateFromBinaryString(number);
        return;
    }
        
    
    if(String::IsValidHexString(number))
    {
        *this = CreateFromHexString(number);
        return;
    }
    
    if(String::IsValidDecimalString(number))
    {
        *this = CreateFromDecimalString(number);
        return;
    }
    
    ASSERT(false);
}

BigInteger BigInteger::CreateWithNChunks(u64 N) {
    ASSERT(N != 0);
    BigInteger a;
    a._chunks.resize(N);
    return a;
}

BigInteger BigInteger::CreateFromBinaryString(const std::string& string) {
    return CreateFromString(2, string);
}

BigInteger BigInteger::CreateFromDecimalString(const std::string& string) {
    return CreateFromString(10, string);
}

BigInteger BigInteger::CreateFromHexString(const std::string& string) {
    return CreateFromString(16, string);
}

u64 BigInteger::NChunks() const {
    return _chunks.size();
}

const u64& BigInteger::ChunkAt(u64 index) const {
    ASSERT(index >= 0 && index < NChunks());
    return _chunks[index];
}

u64& BigInteger::ChunkAt(u64 index) {
    ASSERT(index >= 0 && index < NChunks());
    return _chunks[index];
}

bool BigInteger::Sign() const {
    return _sign;
}

BigInteger::ComparisonResult BigInteger::CompareWith(const BigInteger& other) const {
    if( Sign() == true && other.Sign() == false )
        return Greater;
    if(Sign() == false && other.Sign() == true )
        return Less;
    
    if(NChunks() < other.NChunks())
        return Sign() ? Less : Greater;
    
    if(NChunks() > other.NChunks())
        return Sign() ? Greater : Less;
    
    auto thisChunk = _chunks.rbegin();
    auto otherChunk = other._chunks.rbegin();
    auto endChunk = _chunks.rend();
    
    while(thisChunk != endChunk) {
        if(*thisChunk > *otherChunk)
            return Sign() ? Greater : Less;
        
        if(*thisChunk < *otherChunk)
            return Sign() ? Less : Greater;
        
        ++thisChunk;
        ++otherChunk;
    }
    
    return Equal;
}

BigInteger::ComparisonResult BigInteger::Compare(const BigInteger& first, const BigInteger& second) {
    return first.CompareWith(second);
}

bool operator==( const BigInteger& first, const BigInteger& second) {
    return BigInteger::Compare(first, second) == BigInteger::Equal;
}

bool operator!=( const BigInteger& first, const BigInteger& second) {
    return !(first == second);
}

bool operator>( const BigInteger& first, const BigInteger& second ) {
    return BigInteger::Compare(first, second) == BigInteger::Greater;
}

bool operator>=( const BigInteger& first, const BigInteger& second ) {
    BigInteger::ComparisonResult result = BigInteger::Compare(first, second);
    return (result == BigInteger::Equal) || (result == BigInteger::Greater);
}

bool operator<( const BigInteger& first, const BigInteger& second ) {
    return BigInteger::Compare(first, second) == BigInteger::Less;
}

bool operator<=( const BigInteger& first, const BigInteger& second ) {
    BigInteger::ComparisonResult result = BigInteger::Compare(first, second);
    return (result == BigInteger::Equal) || (result == BigInteger::Less);
}

BigInteger BigInteger::operator+() const {
    BigInteger a = *this;
    a._sign = true;
    return a;
}

BigInteger BigInteger::operator-() const {
    if(NChunks() == 1 && ChunkAt(0) == 0)
        return *this;
    BigInteger a = *this;
    a._sign = !a._sign;
    return a;
}

BigInteger operator+(const BigInteger& first, const BigInteger& second) {
    BigInteger a = first;
    return a += second;
}

BigInteger& BigInteger::operator++() {
    return *this += 1;
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    if(Sign() && other.Sign()) 
        return *this = ApplyFunctionWithoutSign(Function::Add, *this, other);
    
    if(!Sign() && !other.Sign())
        return *this = -ApplyFunctionWithoutSign(Function::Add, *this, other);
        

    if(+(*this) == +other)
        return *this = 0;
    
    if(+(*this) > (+other))
        return *this = Sign() ? ApplyFunctionWithoutSign(Function::Subtract, *this, other) :
                               -ApplyFunctionWithoutSign(Function::Subtract, *this, other);
        
    return *this = Sign() ? -ApplyFunctionWithoutSign(Function::Subtract, other, *this) :
                             ApplyFunctionWithoutSign(Function::Subtract, other, *this);
}

BigInteger operator-(const BigInteger& first, const BigInteger& second) {
    BigInteger a = first;
    return a -= second;
}

BigInteger& BigInteger::operator--() {
    return *this -= 1;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    return *this += -other;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    return *this = *this * other;
}

BigInteger operator*(const BigInteger& first, const BigInteger& second) {
    if(first == 0 || second == 0)
        return 0;
    
    BigInteger chunkToAdd = +second;
    BigInteger result = 0;
    
    for(u64 chunk : first._chunks) {
        for(u8 i = 0; i < BitChunk::BITS_IN_CHUNK; ++i)
        {
            if(BitChunk::GetBitAtIndex(chunk, i))
                result += chunkToAdd;
            chunkToAdd <<= 1;
        }
    }
    result._sign = ((first.Sign() ? 1 : -1) * (second.Sign() ? 1 : -1)) == 1;
    return result;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    return *this = (*this) / other;
}

BigInteger operator/(const BigInteger& first, const BigInteger& second) {
    return BigInteger::Divide(first, second).div;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    return *this = (*this) % other;
}

BigInteger operator%(const BigInteger& first, const BigInteger& second) {
    return BigInteger::Divide(first, second).mod;
}

BigInteger BigInteger::Mod(const BigInteger& other) const {
    return (*this) % other;
}

BigInteger::DivisionResult BigInteger::Divide(const BigInteger& other) const{
    return BigInteger::Divide(*this, other);
}

BigInteger::DivisionResult BigInteger::Divide(const BigInteger& dividend, const BigInteger& divisor) {
    ASSERT(divisor != 0);
    
    BigInteger answer = 0;
    BigInteger chunkToCompare = 0;
    const BigInteger absDivisor = +divisor;
    
    auto it = dividend._chunks.rbegin();
    auto end = dividend._chunks.rend();
    
    while(it != end) {
        for(u8 i = 64; i > 0; --i){
            bool digit = BitChunk::GetBitAtIndex(*it, i-1);
            
            chunkToCompare <<= 1;
            chunkToCompare += ( (digit) ? 1 : 0 );
            chunkToCompare.DeleteZeroChunks();
            
            answer <<= 1;
            if(chunkToCompare >= absDivisor) {
                chunkToCompare -= absDivisor;
                ++answer;
            }
            answer.DeleteZeroChunks();
        }
        ++it;
    }
    
    chunkToCompare.DeleteZeroChunks();
    
    if(dividend.Sign() && divisor.Sign())
        return {answer, chunkToCompare};
    
    if(!dividend.Sign() && !divisor.Sign())
        return {answer, -chunkToCompare};
    
    ++answer;
    answer._sign = false;
    chunkToCompare = absDivisor - chunkToCompare;
    chunkToCompare._sign = divisor.Sign();
    return {answer, chunkToCompare};
}

bool BigInteger::IsOdd() const {
    return IsOdd(*this);
}

bool BigInteger::IsOdd(const BigInteger& a) {
    return !IsEven(a);
}

bool BigInteger::IsEven() const {
    return IsEven(*this);
}

bool BigInteger::IsEven(const BigInteger& a) {
    return BitChunk::GetBitAtIndex(a.ChunkAt(0), 0) == false;
}

BigInteger BigInteger::ToPower(const BigInteger& power) const{
    return Power(*this, power);
}

BigInteger BigInteger::Power(const BigInteger& base, const BigInteger& power) {
    ASSERT(power >= 0);
    
    if(base == 0)
        return 0;
    
    if(power == 0)
        return 1;
    
    if(base == 1)
        return 1;
    
    if(base == -1) {
        BigInteger result = 1;
        result._sign = power.IsEven();
        return result;
    }
    
    std::vector<char> digits = power.GetBinaryCharVector();
    BigInteger result = base;
    
    auto it = std::find(digits.begin(), digits.end(), '1') + 1;
    auto end = digits.end();
    
    while(it != end) {
        result *= result;
        if(*it == '1')
            result *= base;
        ++it;
    }
    
    result._sign = base.Sign() || power.IsEven();
    
    return result;
}

BigInteger BigInteger::operator>>( u8 count ) const {
    BigInteger result = *this;
    return result >>= count;
}

BigInteger& BigInteger::operator>>=( u8 count ) {
    for(u8 i = 0; i < count; ++i) {
        bool carry = false;
        auto it = _chunks.rbegin();
        auto end = _chunks.rend();
        while(it != end) {
            carry = BitChunk::ShiftChunkRightAndReturnCarryBit(*it, carry);
            ++it;
        }
    }
    DeleteZeroChunks();
    return *this;
}

BigInteger BigInteger::operator<<( u8 count ) const {
    BigInteger result = *this;
    return result <<= count;
}

BigInteger& BigInteger::operator<<=( u8 count ) {
    for(u8 i = 0; i < count; ++i) {
        bool carry = false;
        for (u64& chunk : _chunks)
            carry = BitChunk::ShiftChunkLeftAndReturnCarryBit(chunk, carry);
        if(carry)
            _chunks.push_back(1);
    }
    return *this;
}

BigInteger& BigInteger::operator&=( const BigInteger& other) {
    return *this = (*this & other);
}

BigInteger operator&( const BigInteger& first, const BigInteger& second ) {
    return BigInteger::ApplyFunctionWithoutSign(BigInteger::Function::And, first, second);
}

BigInteger& BigInteger::operator|=( const BigInteger& other) {
    return *this = (*this | other);
}

BigInteger operator|( const BigInteger& first, const BigInteger& second ) {
    return BigInteger::ApplyFunctionWithoutSign(BigInteger::Function::Or, first, second);
}

BigInteger& BigInteger::operator^=( const BigInteger& other) {
    return *this = (*this ^ other);
}

BigInteger operator^( const BigInteger& first, const BigInteger& second ) {
    return BigInteger::ApplyFunctionWithoutSign(BigInteger::Function::Xor, first, second);
}

BigInteger BigInteger::operator~() const {
    BigInteger result = *this;
    for (u64& chunk : result._chunks)
        chunk = ~chunk;
    return result;
}

std::vector<bool> BigInteger::GetBinaryVector() const {
    std::vector<char> digits = GetBinaryCharVector();
    std::vector<bool> result(digits.size());
    auto itResult = result.begin();
    auto end = result.end();
    auto itDigits = digits.begin();
    
    while(itResult != end) {
        *itResult = (*itDigits == '1');
        ++itResult;
        ++end;
    }
    return result;
}

std::vector<char> BigInteger::GetBinaryCharVector() const {
    return GetVectorCharRepresentation(2);
}

std::vector<char> BigInteger::GetDecimalVector() const {
    return GetVectorCharRepresentation(10);
}

std::vector<char> BigInteger::GetHexVector() const {
    return GetVectorCharRepresentation(16);
}

std::string BigInteger::ToBinaryString() const {
    return GetStringRepresentation(2);
}

std::string BigInteger::ToDecimalString() const {
    return GetStringRepresentation(10);
}

std::string BigInteger::ToHexString() const {
    return GetStringRepresentation(16);
}

void BigInteger::PrintBinary() const {
    std::cout << ToBinaryString() << '\n';
}

void BigInteger::PrintDecimal() const {
    std::cout << ToDecimalString() << '\n';
}

void BigInteger::PrintHex() const {
    std::cout << ToHexString() << '\n';
}

std::ostream& operator<<(std::ostream& out, const BigInteger& a) {
    out << a.ToDecimalString();
    return out;
}

BigInteger BigInteger::CreateFromString(u8 base, const std::string& string) {
    ASSERT(String::IsValidNumber(base, string));
    
    const u8 minusOffset = (string[0] == '-') ? 1 : 0;
    const u8 prefixLength = String::GetPrefixLengthForBase(base);
    const u8 offset = minusOffset + prefixLength;

    u64 nChunks = NChunksForNDigits(base, string.length() - offset);
    BigInteger result;
    if(base == 10)
        result = 0;
    if((base == 2) || (base == 16))
        result = CreateWithNChunks(nChunks);
    
    const u8 nDigitsInChunk = BitChunk::NDigitsInChunkBase(base);
    
    BigInteger decimalMultiplier = 1;
    
    for(u64 i = 0; i < nChunks - 1; ++i) {
        u64 lastDigitIndex = string.length() - 1 - i * nDigitsInChunk;
        u64 firstDigitIndex = lastDigitIndex - nDigitsInChunk + 1;
        u64 chunk = BitChunk::GetChunkFromDigits(base, string, firstDigitIndex, lastDigitIndex);
        if(base == 10) {
            result += chunk * decimalMultiplier;
            decimalMultiplier *= BitChunk::DECIMAL_BASE;
        }
        if((base == 2) || (base == 16))
            result.ChunkAt(i) = chunk;
    }
    
    u64 lastDigitIndex = string.length() - 1 - (nChunks - 1) * nDigitsInChunk;
    u64 chunk = BitChunk::GetChunkFromDigits(base, string, offset, lastDigitIndex);
    if(base == 10)
        result += chunk * decimalMultiplier;
    if((base == 2) || (base == 16))
        result.ChunkAt(nChunks - 1) = chunk;
    
    result.DeleteZeroChunks();
    result._sign = (minusOffset == 0);
    if(result.NChunks() == 1 && result.ChunkAt(0) == 0)
        result._sign = true;
    return result;
}

void BigInteger::DeleteZeroChunks() {
    u64 zeroChunks = 0;
    auto it = _chunks.rbegin();
    auto end = _chunks.rend() - 1;
    while(it != end) {
        if(*it != 0)
            break;
        ++zeroChunks;
        ++it;
    }
    _chunks.erase(_chunks.end() - zeroChunks, _chunks.end());
}

u64 BigInteger::NChunksForNDigits(u8 base, u64 nDigits) {
    const u8 nDigitsInChunk = BitChunk::NDigitsInChunkBase(base);
    return (nDigits / nDigitsInChunk) + ((nDigits % nDigitsInChunk) == 0 ? 0 : 1);
}

BigInteger BigInteger::ApplyFunctionWithoutSign(Function function, const BigInteger& first, const BigInteger& second) {
    if(function == Function::Subtract)
        ASSERT(+first > +second);
    const BigInteger& biggest  = (first.NChunks() >= second.NChunks()) ? first : second;
    const BigInteger& smallest = (first.NChunks() >= second.NChunks()) ? second : first;
    auto result = BigInteger::CreateWithNChunks(biggest.NChunks());
    
    auto itResult = result._chunks.begin();
    auto itBig = biggest._chunks.begin();
    auto itBigEnd = biggest._chunks.end();
    auto itSmall = smallest._chunks.begin();
    auto itSmallEnd = smallest._chunks.end();
    
    bool carry = false;
    bool isBorrow = false;
    
    while(itSmall != itSmallEnd) {
        switch (function) {
            case Function::Xor:
                *itResult = *itBig ^ *itSmall;
                break;
            case Function::And:
                *itResult = *itBig & *itSmall;
                break;
            case Function::Or:
                *itResult = *itBig | *itSmall;
                break;
            case Function::Add:
                *itResult = *itBig;
                carry = BitChunk::AddChunksAndReturnCarryBit(*itResult, *itSmall, carry);
                break;
            case Function::Subtract:
                *itResult = *itBig;
                isBorrow = BitChunk::SubtractChunksAndReturnIfBorrow(*itResult, *itSmall, isBorrow);
                break;
        }
        ++itResult;
        ++itSmall;
        ++itBig;
    }
    
    while(itBig != itBigEnd) {
        switch (function) {
            case Function::Xor:
                *itResult = *itBig;
                break;
            case Function::And:
                *itResult = 0;
                break;
            case Function::Or:
                *itResult = *itBig;
                break;
            case Function::Add:
                *itResult = *itBig;
                carry = BitChunk::AddChunksAndReturnCarryBit(*itResult, 0, carry);
                break;
            case Function::Subtract:
                *itResult = *itBig;
                isBorrow = BitChunk::SubtractChunksAndReturnIfBorrow(*itResult, 0, isBorrow);
                break;
        }
        ++itResult;
        ++itBig;
    }
    
    if(carry)
        result._chunks.push_back(1);
    
    ASSERT(!isBorrow);
    
    result.DeleteZeroChunks();
    return result;
}

std::string BigInteger::GetStringRepresentation( u8 base ) const {
    std::string result = Sign() ? "" : "-";
    result += String::GetPrefixForBase(base);
    if(*this == 0)
        return result += "0";
    bool isPrinting = false;
    std::vector<char> digits = GetVectorCharRepresentation(base);
    for (char digit : digits) {
        if(!isPrinting)
            isPrinting = (digit != '0');
        if(isPrinting)
            result += digit;
    }
    return result;
}

std::vector<char> BigInteger::GetVectorCharRepresentation( u8 base ) const {
    if(base == 10)
        return GetVectorCharDecimalRepresentation();
    std::vector<char> result;
    result.reserve(BitChunk::NDigitsInChunkBase(base) * NChunks());
    auto it = _chunks.rbegin();
    auto end = _chunks.rend();
    while(it != end){
        std::vector<char> chunkDigits = String::GetCharVectorFromChunk(base, *it);
        for (char digit : chunkDigits)
            result.push_back(digit);
        ++it;
    }
    return result;
}

std::vector<char> BigInteger::GetVectorCharDecimalRepresentation() const {
    std::vector<char> answer;
    answer.reserve(BitChunk::DECIMAL_BASE_N_DIGITS * NChunks());
    
    BigInteger absValue = +(*this);
    
    while(absValue > 0) {
        auto result = absValue.Divide(BitChunk::DECIMAL_BASE);
        std::vector<char> chunkDigits = String::GetCharVectorFromChunk(10, result.mod.ChunkAt(0));
        absValue = result.div;
        answer.insert(answer.begin(), chunkDigits.begin(), chunkDigits.end());
    }
    
    return answer;
}




}
