#ifndef StringTests_hpp
#define StringTests_hpp

#include "TestClass.hpp"
#include "String.hpp"

namespace StringTests {

using namespace AmvilinaCore;

bool AreEqualCharVectors(const std::vector<char> first, const std::vector<char> second);

TEST_CLASS_BEGIN(StringTest)

TEST_METHOD(IsValidDigit)
{
    MUST_BE_TRUE(String::IsValidDigit(2, '0'));
    MUST_BE_TRUE(String::IsValidDigit(2, '1'));
    
    MUST_BE_FALSE(String::IsValidDigit(2, '2'));
    MUST_BE_FALSE(String::IsValidDigit(2, 'G'));
    MUST_BE_FALSE(String::IsValidDigit(2, '-'));
    
    MUST_BE_TRUE(String::IsValidDigit(10, '0'));
    MUST_BE_TRUE(String::IsValidDigit(10, '5'));
    MUST_BE_TRUE(String::IsValidDigit(10, '9'));
    
    MUST_BE_FALSE(String::IsValidDigit(10, 'a'));
    MUST_BE_FALSE(String::IsValidDigit(10, 'G'));
    MUST_BE_FALSE(String::IsValidDigit(10, '-'));
    
    MUST_BE_TRUE(String::IsValidDigit(16, '0'));
    MUST_BE_TRUE(String::IsValidDigit(16, '5'));
    MUST_BE_TRUE(String::IsValidDigit(16, '9'));
    MUST_BE_TRUE(String::IsValidDigit(16, 'A'));
    MUST_BE_TRUE(String::IsValidDigit(16, 'f'));
    
    MUST_BE_FALSE(String::IsValidDigit(16, 'g'));
    MUST_BE_FALSE(String::IsValidDigit(16, 'G'));
    MUST_BE_FALSE(String::IsValidDigit(16, 'z'));
    MUST_BE_FALSE(String::IsValidDigit(16, 'J'));
    MUST_BE_FALSE(String::IsValidDigit(16, '*'));
    MUST_BE_FALSE(String::IsValidDigit(16, '-'));
}

TEST_METHOD(IsValidDigit_Wrong_Base_Assert)
{
    MUST_ASSERT(String::IsValidDigit(1, ' '));
    MUST_ASSERT(String::IsValidDigit(3, ' '));
    MUST_ASSERT(String::IsValidDigit(9, ' '));
    MUST_ASSERT(String::IsValidDigit(11, ' '));
    MUST_ASSERT(String::IsValidDigit(100, ' '));
    MUST_ASSERT(String::IsValidDigit(17, ' '));
}

TEST_METHOD(IsBinaryDigit)
{
    MUST_BE_TRUE(String::IsBinaryDigit('0'));
    MUST_BE_TRUE(String::IsBinaryDigit('1'));
    
    MUST_BE_FALSE(String::IsBinaryDigit('2'));
    MUST_BE_FALSE(String::IsBinaryDigit('5'));
    MUST_BE_FALSE(String::IsBinaryDigit('9'));
    MUST_BE_FALSE(String::IsBinaryDigit('a'));
    MUST_BE_FALSE(String::IsBinaryDigit('Z'));
    MUST_BE_FALSE(String::IsBinaryDigit('f'));
    MUST_BE_FALSE(String::IsBinaryDigit('B'));
    MUST_BE_FALSE(String::IsBinaryDigit('^'));
}

TEST_METHOD(IsDecimalDigit)
{
    MUST_BE_TRUE(String::IsDigit('0'));
    MUST_BE_TRUE(String::IsDigit('3'));
    MUST_BE_TRUE(String::IsDigit('5'));
    MUST_BE_TRUE(String::IsDigit('9'));
    
    MUST_BE_FALSE(String::IsDigit('a'));
    MUST_BE_FALSE(String::IsDigit('A'));
    MUST_BE_FALSE(String::IsDigit('z'));
    MUST_BE_FALSE(String::IsDigit('Z'));
    MUST_BE_FALSE(String::IsDigit('f'));
    MUST_BE_FALSE(String::IsDigit('F'));
    MUST_BE_FALSE(String::IsDigit('q'));
    MUST_BE_FALSE(String::IsDigit(':'));
    MUST_BE_FALSE(String::IsDigit('!'));
}

TEST_METHOD(IsDigit)
{
    MUST_BE_TRUE(String::IsDigit('0'));
    MUST_BE_TRUE(String::IsDigit('1'));
    MUST_BE_TRUE(String::IsDigit('5'));
    MUST_BE_TRUE(String::IsDigit('9'));
    
    MUST_BE_FALSE(String::IsDigit('a'));
    MUST_BE_FALSE(String::IsDigit('A'));
    MUST_BE_FALSE(String::IsDigit('z'));
    MUST_BE_FALSE(String::IsDigit('Z'));
    MUST_BE_FALSE(String::IsDigit('f'));
    MUST_BE_FALSE(String::IsDigit('F'));
    MUST_BE_FALSE(String::IsDigit('+'));
    MUST_BE_FALSE(String::IsDigit(' '));
    MUST_BE_FALSE(String::IsDigit('.'));
}

TEST_METHOD(IsHexDigit)
{
    MUST_BE_TRUE(String::IsHexDigit('0'));
    MUST_BE_TRUE(String::IsHexDigit('1'));
    MUST_BE_TRUE(String::IsHexDigit('8'));
    MUST_BE_TRUE(String::IsHexDigit('9'));
    MUST_BE_TRUE(String::IsHexDigit('a'));
    MUST_BE_TRUE(String::IsHexDigit('A'));
    MUST_BE_TRUE(String::IsHexDigit('f'));
    MUST_BE_TRUE(String::IsHexDigit('F'));
    
    MUST_BE_FALSE(String::IsHexDigit('z'));
    MUST_BE_FALSE(String::IsHexDigit('Z'));
    MUST_BE_FALSE(String::IsHexDigit('+'));
    MUST_BE_FALSE(String::IsHexDigit(' '));
    MUST_BE_FALSE(String::IsHexDigit('.'));
    MUST_BE_FALSE(String::IsHexDigit('V'));
    MUST_BE_FALSE(String::IsHexDigit('j'));
    MUST_BE_FALSE(String::IsHexDigit('-'));
    MUST_BE_FALSE(String::IsHexDigit('|'));
}

TEST_METHOD(IsHexLetter)
{
    MUST_BE_TRUE(String::IsHexLetter('A'));
    MUST_BE_TRUE(String::IsHexLetter('b'));
    MUST_BE_TRUE(String::IsHexLetter('C'));
    MUST_BE_TRUE(String::IsHexLetter('d'));
    MUST_BE_TRUE(String::IsHexLetter('E'));
    MUST_BE_TRUE(String::IsHexLetter('F'));
    
    MUST_BE_FALSE(String::IsHexLetter('G'));
    MUST_BE_FALSE(String::IsHexLetter('v'));
    MUST_BE_FALSE(String::IsHexLetter('0'));
    MUST_BE_FALSE(String::IsHexLetter('1'));
    MUST_BE_FALSE(String::IsHexLetter('-'));
    MUST_BE_FALSE(String::IsHexLetter(' '));
    MUST_BE_FALSE(String::IsHexLetter('|'));
}

TEST_METHOD(ToLower)
{
    MUST_BE_TRUE(String::ToLower('A') == 'a');
    MUST_BE_TRUE(String::ToLower('B') == 'b');
    MUST_BE_TRUE(String::ToLower('Z') == 'z');
    MUST_BE_TRUE(String::ToLower('a') == 'a');
    MUST_BE_TRUE(String::ToLower('h') == 'h');
    MUST_BE_TRUE(String::ToLower('z') == 'z');
    MUST_BE_TRUE(String::ToLower('}') == '}');
    MUST_BE_TRUE(String::ToLower('+') == '+');
    MUST_BE_TRUE(String::ToLower(' ') == ' ');
}

TEST_METHOD(IsLetter)
{
    MUST_BE_TRUE(String::IsLetter('A'));
    MUST_BE_TRUE(String::IsLetter('B'));
    MUST_BE_TRUE(String::IsLetter('G'));
    MUST_BE_TRUE(String::IsLetter('Z'));
    MUST_BE_TRUE(String::IsLetter('a'));
    MUST_BE_TRUE(String::IsLetter('b'));
    MUST_BE_TRUE(String::IsLetter('g'));
    MUST_BE_TRUE(String::IsLetter('z'));
    
    MUST_BE_FALSE(String::IsLetter('0'));
    MUST_BE_FALSE(String::IsLetter('}'));
    MUST_BE_FALSE(String::IsLetter('8'));
    MUST_BE_FALSE(String::IsLetter('-'));
}

TEST_METHOD(DigitValue)
{
    MUST_BE_TRUE(String::DigitValue(2, '0') == 0);
    MUST_BE_TRUE(String::DigitValue(2, '1') == 1);
    
    MUST_BE_TRUE(String::DigitValue(10, '0') == 0);
    MUST_BE_TRUE(String::DigitValue(10, '3') == 3);
    MUST_BE_TRUE(String::DigitValue(10, '9') == 9);
    
    MUST_BE_TRUE(String::DigitValue(16, '0') == 0);
    MUST_BE_TRUE(String::DigitValue(16, '2') == 2);
    MUST_BE_TRUE(String::DigitValue(16, '5') == 5);
    MUST_BE_TRUE(String::DigitValue(16, '9') == 9);
    MUST_BE_TRUE(String::DigitValue(16, 'a') == 10);
    MUST_BE_TRUE(String::DigitValue(16, 'D') == 13);
    MUST_BE_TRUE(String::DigitValue(16, 'F') == 15);
}

TEST_METHOD(DigitValue_Wrong_Base_Assert)
{
    MUST_ASSERT(String::DigitValue(1, ' '));
    MUST_ASSERT(String::DigitValue(3, ' '));
    MUST_ASSERT(String::DigitValue(9, ' '));
    MUST_ASSERT(String::DigitValue(22, ' '));
}

TEST_METHOD(DigitValue_Not_Valid_Number_Assert)
{
    MUST_ASSERT(String::DigitValue(2, '3'));
    MUST_ASSERT(String::DigitValue(2, '='));
    MUST_ASSERT(String::DigitValue(2, '8'));
    MUST_ASSERT(String::DigitValue(2, 'A'));
    
    MUST_ASSERT(String::DigitValue(10, 'a'));
    MUST_ASSERT(String::DigitValue(10, '='));
    MUST_ASSERT(String::DigitValue(10, 'H'));
    MUST_ASSERT(String::DigitValue(10, '$'));
    
    MUST_ASSERT(String::DigitValue(16, 'g'));
    MUST_ASSERT(String::DigitValue(16, 'G'));
    MUST_ASSERT(String::DigitValue(16, 'J'));
    MUST_ASSERT(String::DigitValue(16, 'l'));
    MUST_ASSERT(String::DigitValue(16, ')'));
    MUST_ASSERT(String::DigitValue(16, '@'));
}

TEST_METHOD(HexValueForDigit)
{
    MUST_BE_TRUE(String::HexValueForDigit('0') == 0);
    MUST_BE_TRUE(String::HexValueForDigit('3') == 3);
    MUST_BE_TRUE(String::HexValueForDigit('9') == 9);
    MUST_BE_TRUE(String::HexValueForDigit('a') == 10);
    MUST_BE_TRUE(String::HexValueForDigit('B') == 11);
    MUST_BE_TRUE(String::HexValueForDigit('c') == 12);
    MUST_BE_TRUE(String::HexValueForDigit('D') == 13);
    MUST_BE_TRUE(String::HexValueForDigit('e') == 14);
    MUST_BE_TRUE(String::HexValueForDigit('F') == 15);
}

TEST_METHOD(HexValueForDigit_Not_Hex_Assert)
{
    MUST_ASSERT(String::HexValueForDigit('g'));
    MUST_ASSERT(String::HexValueForDigit('G'));
    MUST_ASSERT(String::HexValueForDigit('z'));
    MUST_ASSERT(String::HexValueForDigit('H'));
    MUST_ASSERT(String::HexValueForDigit('.'));
    MUST_ASSERT(String::HexValueForDigit('-'));
    MUST_ASSERT(String::HexValueForDigit(' '));
}

TEST_METHOD(GetCharFromValue) {
    MUST_BE_TRUE(String::GetCharFromValue(2, 0) == '0');
    MUST_BE_TRUE(String::GetCharFromValue(2, 1) == '1');
    
    MUST_BE_TRUE(String::GetCharFromValue(10, 0) == '0');
    MUST_BE_TRUE(String::GetCharFromValue(10, 1) == '1');
    MUST_BE_TRUE(String::GetCharFromValue(10, 5) == '5');
    MUST_BE_TRUE(String::GetCharFromValue(10, 9) == '9');
    
    MUST_BE_TRUE(String::GetCharFromValue(16, 0) == '0');
    MUST_BE_TRUE(String::GetCharFromValue(16, 1) == '1');
    MUST_BE_TRUE(String::GetCharFromValue(16, 9) == '9');
    MUST_BE_TRUE(String::GetCharFromValue(16, 10) == 'A');
    MUST_BE_TRUE(String::GetCharFromValue(16, 13) == 'D');
    MUST_BE_TRUE(String::GetCharFromValue(16, 15) == 'F');
}

TEST_METHOD(GetCharFromValue_Wrong_Base_Assert)
{
    MUST_ASSERT(String::GetCharFromValue(1, 0));
    MUST_ASSERT(String::GetCharFromValue(3, 0));
    MUST_ASSERT(String::GetCharFromValue(7, 0));
    MUST_ASSERT(String::GetCharFromValue(18, 0));
}

TEST_METHOD(GetCharFromValue_Not_Valid_Value_Assert)
{
    MUST_ASSERT(String::GetCharFromValue(2, 3));
    MUST_ASSERT(String::GetCharFromValue(2, 14));
    
    MUST_ASSERT(String::GetCharFromValue(10, 10));
    MUST_ASSERT(String::GetCharFromValue(10, 11));
    MUST_ASSERT(String::GetCharFromValue(10, 25));
    
    MUST_ASSERT(String::GetCharFromValue(16, 16));
    MUST_ASSERT(String::GetCharFromValue(16, 17));
    MUST_ASSERT(String::GetCharFromValue(16, 34));
}

TEST_METHOD(GetCharFromBinaryValue)
{
    MUST_BE_TRUE(String::GetCharFromBinaryValue(0) == '0');
    MUST_BE_TRUE(String::GetCharFromBinaryValue(1) == '1');
}

TEST_METHOD(GetCharFromBinaryValue_Out_Of_Range_Value_Assert)
{
    MUST_ASSERT(String::GetCharFromBinaryValue(3));
    MUST_ASSERT(String::GetCharFromBinaryValue(4));
    MUST_ASSERT(String::GetCharFromBinaryValue(100));
}

TEST_METHOD(GetCharFromDecimalValue)
{
    MUST_BE_TRUE(String::GetCharFromDecimalValue(0) == '0');
    MUST_BE_TRUE(String::GetCharFromDecimalValue(6) == '6');
    MUST_BE_TRUE(String::GetCharFromDecimalValue(9) == '9');
}

TEST_METHOD(GetCharFromDecimalValue_Out_Of_Range_Value_Assert)
{
    MUST_ASSERT(String::GetCharFromDecimalValue(10));
    MUST_ASSERT(String::GetCharFromDecimalValue(11));
    MUST_ASSERT(String::GetCharFromDecimalValue(33));
}

TEST_METHOD(GetCharFromHexValue)
{
    MUST_BE_TRUE(String::GetCharFromHexValue(0) == '0');
    MUST_BE_TRUE(String::GetCharFromHexValue(2) == '2');
    MUST_BE_TRUE(String::GetCharFromHexValue(9) == '9');
    MUST_BE_TRUE(String::GetCharFromHexValue(10) == 'A');
    MUST_BE_TRUE(String::GetCharFromHexValue(12) == 'C');
    MUST_BE_TRUE(String::GetCharFromHexValue(15) == 'F');
}

TEST_METHOD(GetCharFromHexValue_Out_Of_Range_Value_Assert)
{
    MUST_ASSERT(String::GetCharFromHexValue(16));
    MUST_ASSERT(String::GetCharFromHexValue(17));
    MUST_ASSERT(String::GetCharFromHexValue(58));
}

TEST_METHOD(IsValidPrefix)
{
    MUST_BE_TRUE(String::IsValidPrefix(2, "0b"));
    MUST_BE_TRUE(String::IsValidPrefix(10, ""));
    MUST_BE_TRUE(String::IsValidPrefix(16, "0x"));
    
    MUST_BE_FALSE(String::IsValidPrefix(2, "0"));
    MUST_BE_FALSE(String::IsValidPrefix(2, "b"));
    MUST_BE_FALSE(String::IsValidPrefix(2, "0x"));
    MUST_BE_FALSE(String::IsValidPrefix(2, ""));
    
    MUST_BE_FALSE(String::IsValidPrefix(10, "0"));
    MUST_BE_FALSE(String::IsValidPrefix(10, "b"));
    MUST_BE_FALSE(String::IsValidPrefix(10, "0x"));
    MUST_BE_FALSE(String::IsValidPrefix(10, " "));
    
    MUST_BE_FALSE(String::IsValidPrefix(16, "0"));
    MUST_BE_FALSE(String::IsValidPrefix(16, "x"));
    MUST_BE_FALSE(String::IsValidPrefix(16, "0b"));
    MUST_BE_FALSE(String::IsValidPrefix(16, ""));
}

TEST_METHOD(IsValidPrefix_Wrong_Base_Assert)
{
    MUST_ASSERT(String::IsValidPrefix(0, ""));
    MUST_ASSERT(String::IsValidPrefix(3, ""));
    MUST_ASSERT(String::IsValidPrefix(9, ""));
    MUST_ASSERT(String::IsValidPrefix(23, ""));
}

TEST_METHOD(GetPrefixForBase)
{
    MUST_BE_TRUE(String::GetPrefixForBase(2) == "0b");
    MUST_BE_TRUE(String::GetPrefixForBase(10) == "");
    MUST_BE_TRUE(String::GetPrefixForBase(16) == "0x");
}

TEST_METHOD(GetPrefixForBase_Wrong_Base_Assert)
{
    MUST_ASSERT(String::GetPrefixForBase(0));
    MUST_ASSERT(String::GetPrefixForBase(1));
    MUST_ASSERT(String::GetPrefixForBase(5));
    MUST_ASSERT(String::GetPrefixForBase(21));
}

TEST_METHOD(GetPrefixLengthForBase)
{
    MUST_BE_TRUE(String::GetPrefixLengthForBase(2) == 2);
    MUST_BE_TRUE(String::GetPrefixLengthForBase(10) == 0);
    MUST_BE_TRUE(String::GetPrefixLengthForBase(16) == 2);
}

TEST_METHOD(GetPrefixLengthForBase_Wrong_Base_Assert)
{
    MUST_ASSERT(String::GetPrefixLengthForBase(0));
    MUST_ASSERT(String::GetPrefixLengthForBase(1));
    MUST_ASSERT(String::GetPrefixLengthForBase(5));
    MUST_ASSERT(String::GetPrefixLengthForBase(21));
}


TEST_METHOD(IsValidNumber)
{
    MUST_BE_TRUE(String::IsValidNumber(2, "0b10101"));
    MUST_BE_TRUE(String::IsValidNumber(2, "0b1"));
    MUST_BE_TRUE(String::IsValidNumber(2, "-0b1111010110101001011110101011001"));
    
    MUST_BE_FALSE(String::IsValidNumber(2, " 0b10101"));
    MUST_BE_FALSE(String::IsValidNumber(2, "0b"));
    MUST_BE_FALSE(String::IsValidNumber(2, "- 0b1111010110101001011110101011001"));
    
    MUST_BE_TRUE(String::IsValidNumber(10, "21985125"));
    MUST_BE_TRUE(String::IsValidNumber(10, "0"));
    MUST_BE_TRUE(String::IsValidNumber(10, "-1"));
    
    MUST_BE_FALSE(String::IsValidNumber(10, ""));
    MUST_BE_FALSE(String::IsValidNumber(10, "8141f021412"));
    MUST_BE_FALSE(String::IsValidNumber(10, "-1918080018025."));
    
    MUST_BE_TRUE(String::IsValidNumber(16, "0x315FafCb"));
    MUST_BE_TRUE(String::IsValidNumber(16, "0x0"));
    MUST_BE_TRUE(String::IsValidNumber(16, "-0x14FFFFAC"));
    
    MUST_BE_FALSE(String::IsValidNumber(16, "0x315 FafCb"));
    MUST_BE_FALSE(String::IsValidNumber(16, "0"));
    MUST_BE_FALSE(String::IsValidNumber(16, "--0x135Fac"));
}

TEST_METHOD(IsValidNumber_Wrong_Base_Assert)
{
    MUST_ASSERT(String::IsValidNumber(0, ""));
    MUST_ASSERT(String::IsValidNumber(1, ""));
    MUST_ASSERT(String::IsValidNumber(6, ""));
    MUST_ASSERT(String::IsValidNumber(13, ""));
}

TEST_METHOD(IsValidBinaryString)
{
    MUST_BE_TRUE(String::IsValidBinaryString("0b10110101"));
    MUST_BE_TRUE(String::IsValidBinaryString("0b1"));
    MUST_BE_TRUE(String::IsValidBinaryString("0b0"));
    MUST_BE_TRUE(String::IsValidBinaryString("-0b1010101"));
    
    MUST_BE_FALSE(String::IsValidBinaryString(""));
    MUST_BE_FALSE(String::IsValidBinaryString(" "));
    MUST_BE_FALSE(String::IsValidBinaryString(" 0b"));
    MUST_BE_FALSE(String::IsValidBinaryString("0b"));
    MUST_BE_FALSE(String::IsValidBinaryString("-"));
    MUST_BE_FALSE(String::IsValidBinaryString("0"));
    MUST_BE_FALSE(String::IsValidBinaryString("-0b5"));
    MUST_BE_FALSE(String::IsValidBinaryString("010100101"));
    MUST_BE_FALSE(String::IsValidBinaryString("0x101010101"));
    MUST_BE_FALSE(String::IsValidBinaryString("0b12101"));
    MUST_BE_FALSE(String::IsValidBinaryString("0b1a101"));
}

TEST_METHOD(IsValidDecimalString)
{
    MUST_BE_TRUE(String::IsValidDecimalString("28150241"));
    MUST_BE_TRUE(String::IsValidDecimalString("000000"));
    MUST_BE_TRUE(String::IsValidDecimalString("-0"));
    MUST_BE_TRUE(String::IsValidDecimalString("-24151251"));
    MUST_BE_TRUE(String::IsValidDecimalString("99999"));
    
    MUST_BE_FALSE(String::IsValidDecimalString(""));
    MUST_BE_FALSE(String::IsValidDecimalString(" "));
    MUST_BE_FALSE(String::IsValidDecimalString(" 124"));
    MUST_BE_FALSE(String::IsValidDecimalString("3141f"));
    MUST_BE_FALSE(String::IsValidDecimalString("--125125"));
    MUST_BE_FALSE(String::IsValidDecimalString("adjdlkfja"));
    MUST_BE_FALSE(String::IsValidDecimalString("oo2131"));
}

TEST_METHOD(IsValidHexString)
{
    MUST_BE_TRUE(String::IsValidHexString("0x1234567890"));
    MUST_BE_TRUE(String::IsValidHexString("0xabcdef"));
    MUST_BE_TRUE(String::IsValidHexString("0xABCDEF"));
    MUST_BE_TRUE(String::IsValidHexString("0xaAbBcCdDeEfF"));
    MUST_BE_TRUE(String::IsValidHexString("0x82Fc82AcbE3351"));
    MUST_BE_TRUE(String::IsValidHexString("-0x8255F41BA"));
    
    MUST_BE_FALSE(String::IsValidHexString(""));
    MUST_BE_FALSE(String::IsValidHexString(" "));
    MUST_BE_FALSE(String::IsValidHexString(" 0x"));
    MUST_BE_FALSE(String::IsValidHexString("0x"));
    MUST_BE_FALSE(String::IsValidHexString("-0x"));
    MUST_BE_FALSE(String::IsValidHexString("-0"));
    MUST_BE_FALSE(String::IsValidHexString("-"));
    MUST_BE_FALSE(String::IsValidHexString("-0xj"));
    MUST_BE_FALSE(String::IsValidHexString("98518925195"));
    MUST_BE_FALSE(String::IsValidHexString("abcdef"));
    MUST_BE_FALSE(String::IsValidHexString("ABCDEF"));
    MUST_BE_FALSE(String::IsValidHexString("0b101aB7dC1"));
    MUST_BE_FALSE(String::IsValidHexString("0xabcdefg"));
    MUST_BE_FALSE(String::IsValidHexString("0xABCDEFG"));
    MUST_BE_FALSE(String::IsValidHexString("0xaAbBcCdDeEfFgG"));
    MUST_BE_FALSE(String::IsValidHexString("0x185891dfjbc"));
    MUST_BE_FALSE(String::IsValidHexString("0xfc35aoVjQ"));
}

TEST_METHOD(GetCharVectorFromChunk)
{
    std::vector<char> binaryVector(64, '0');
    binaryVector[63] = '1';
    binaryVector[61] = '1';
    binaryVector[60] = '1';
    MUST_BE_TRUE(AreEqualCharVectors(String::GetCharVectorFromChunk(2, 13), binaryVector));
    
    std::vector<char> decimalVector(18, '0');
    decimalVector[0] = '1';
    decimalVector[6] = '8';
    decimalVector[11] = '3';
    MUST_BE_TRUE(AreEqualCharVectors(String::GetCharVectorFromChunk(10, 100000800003000000), decimalVector));
    
    std::vector<char> hexVector(16, '0');
    hexVector[0] = 'F';
    hexVector[13] = '5';
    hexVector[15] = 'C';
    MUST_BE_TRUE(AreEqualCharVectors(String::GetCharVectorFromChunk(16, 0xF00000000000050C), hexVector));
}

TEST_METHOD(GetCharVectorFromChunk_Wrong_Base_Assert)
{
    MUST_ASSERT(String::GetCharVectorFromChunk(0, 0));
    MUST_ASSERT(String::GetCharVectorFromChunk(1, 0));
    MUST_ASSERT(String::GetCharVectorFromChunk(9, 0));
    MUST_ASSERT(String::GetCharVectorFromChunk(13, 0));
}

TEST_CLASS_END(StringTest)

bool AreEqualCharVectors(const std::vector<char> first, const std::vector<char> second)
{
    if(first.size() != second.size())
        return false;
    
    auto itFirst = first.begin();
    auto itFirstEnd = first.end();
    auto itSecond = second.begin();
    
    while(itFirst != itFirstEnd){
        if(*itFirst != *itSecond)
            return false;
        ++itFirst;
        ++itSecond;
    }
    return true;
}

}
#endif
