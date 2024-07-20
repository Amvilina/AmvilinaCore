#ifndef BigIntegerTests_hpp
#define BigIntegerTests_hpp

#include "TestClass.hpp"
#include "BigInteger.hpp"


namespace BigIntegerTests {
using namespace AmvilinaCore;

TEST_CLASS_BEGIN(BigIntegerTest)

TEST_METHOD(Default_Constructor)
{
    BigInteger a;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 0);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(u8_Constructor)
{
    u8 i = 13;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 13);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(i8_Constructor)
{
    i8 i = -13;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 13);
    MUST_BE_TRUE(a.Sign() == false);
}

TEST_METHOD(u16_Constructor)
{
    u16 i = 14824;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 14824);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(i16_Constructor)
{
    i16 i = -1143;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 1143);
    MUST_BE_TRUE(a.Sign() == false);
}

TEST_METHOD(u32_Constructor)
{
    u32 i = 14351824;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 14351824);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(i32_Constructor)
{
    i32 i = -1143922;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 1143922);
    MUST_BE_TRUE(a.Sign() == false);
}

TEST_METHOD(u64_Constructor)
{
    u64 i = 147512351824;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 147512351824);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(i64_Constructor)
{
    i64 i = -1929143922;
    BigInteger a = i;
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 1929143922);
    MUST_BE_TRUE(a.Sign() == false);
}

TEST_METHOD(ChunkAt_Out_Of_Range_Assert)
{
    BigInteger a;
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_ASSERT(a.ChunkAt(1));
}

TEST_METHOD(CreateWithNChunks)
{
    auto a = BigInteger::CreateWithNChunks(13);
    
    MUST_BE_TRUE(a.NChunks() == 13);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(CreateWithNChunks_Zero_Assert)
{
    MUST_ASSERT(BigInteger::CreateWithNChunks(0));
}

TEST_METHOD(CreateFromBinaryString)
{
    auto a = BigInteger::CreateFromBinaryString("0b101010101");
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 0b101010101);
    MUST_BE_TRUE(a.Sign() == true);
    
    auto b = BigInteger::CreateFromBinaryString("-0b1111111111111111111111111111111111111111111111111111111111111111");
    
    MUST_BE_TRUE(b.NChunks() == 1);
    MUST_BE_TRUE(b.ChunkAt(0) == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(b.Sign() == false);
    
    auto c = BigInteger::CreateFromBinaryString("0b11111111111111111111111111111111111111111111111111111111111111111");
    
    MUST_BE_TRUE(c.NChunks() == 2);
    MUST_BE_TRUE(c.ChunkAt(0) == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(c.ChunkAt(1) == 1);
    MUST_BE_TRUE(c.Sign() == true);
    
    auto d = BigInteger::CreateFromBinaryString("-0b100111111111111110001111111100111100111111101111111000111111111101111111001111111");
    
    MUST_BE_TRUE(d.NChunks() == 2);
    MUST_BE_TRUE(d.ChunkAt(0) == 0b0001111111100111100111111101111111000111111111101111111001111111);
    MUST_BE_TRUE(d.ChunkAt(1) == 0b10011111111111111);
    MUST_BE_TRUE(d.Sign() == false);
}

TEST_METHOD(CreateFromBinaryString_Not_Valid_Assert)
{
    MUST_ASSERT(BigInteger::CreateFromBinaryString("0b"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("010100101"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("0x101010101"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("0b12101"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("0b1a101"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("-"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("0"));
    MUST_ASSERT(BigInteger::CreateFromBinaryString("-0b5"));
}

TEST_METHOD(CreateFromHexString)
{
    auto a = BigInteger::CreateFromHexString("0xfA1c2B13");
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 0xFA1C2B13);
    MUST_BE_TRUE(a.Sign() == true);
    
    auto b = BigInteger::CreateFromHexString("-0xFFFFFFFFFFFFFFFF");
    MUST_BE_TRUE(b.NChunks() == 1);
    MUST_BE_TRUE(b.ChunkAt(0) == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(b.Sign() == false);
    
    auto c = BigInteger::CreateFromHexString("0xFFFFFFFFFFFFFFFFF");
    MUST_BE_TRUE(c.NChunks() == 2);
    MUST_BE_TRUE(c.ChunkAt(0) == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(c.ChunkAt(1) == 0xF);
    MUST_BE_TRUE(c.Sign() == true);
    
    auto d = BigInteger::CreateFromHexString("-0x72fC9d9e96A967B96a86c96d0E968f0896b589a9875b6dF");
    MUST_BE_TRUE(d.NChunks() == 3);
    MUST_BE_TRUE(d.ChunkAt(0) == 0x896B589A9875B6DF);
    MUST_BE_TRUE(d.ChunkAt(1) == 0x96A86C96D0E968F0);
    MUST_BE_TRUE(d.ChunkAt(2) == 0x72fC9d9e96A967B);
    MUST_BE_TRUE(d.Sign() == false);
}

TEST_METHOD(CreateFromHexString_Not_Valid_Assert)
{
    MUST_ASSERT(BigInteger::CreateFromHexString("0x"));
    MUST_ASSERT(BigInteger::CreateFromHexString("-0x"));
    MUST_ASSERT(BigInteger::CreateFromHexString("-0"));
    MUST_ASSERT(BigInteger::CreateFromHexString("-"));
    MUST_ASSERT(BigInteger::CreateFromHexString("-0xj"));
    MUST_ASSERT(BigInteger::CreateFromHexString("98518925195"));
    MUST_ASSERT(BigInteger::CreateFromHexString("0b101aB7dC1"));
    MUST_ASSERT(BigInteger::CreateFromHexString("abcdef"));
    MUST_ASSERT(BigInteger::CreateFromHexString("0xABCDEFG"));
    MUST_ASSERT(BigInteger::CreateFromHexString("0xaAbBcCdDeEfFgG"));
    MUST_ASSERT(BigInteger::CreateFromHexString("0x185891dfjbc"));
    MUST_ASSERT(BigInteger::CreateFromHexString("0xfc35aoVjQ"));
}

TEST_METHOD(CreateFromDecimalString)
{
    auto a = BigInteger::CreateFromDecimalString("47812841");
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a.ChunkAt(0) == 47812841);
    MUST_BE_TRUE(a.Sign() == true);
    
    auto b = BigInteger::CreateFromDecimalString("18446744073709551615");
    MUST_BE_TRUE(b.NChunks() == 1);
    MUST_BE_TRUE(b.ChunkAt(0) == BitChunk::MAX_VALUE);
    MUST_BE_TRUE(b.Sign() == true);
    
    auto c = BigInteger::CreateFromDecimalString("-0");
    MUST_BE_TRUE(c.NChunks() == 1);
    MUST_BE_TRUE(c.ChunkAt(0) == 0);
    MUST_BE_TRUE(c.Sign() == true);
    
    auto d = BigInteger::CreateFromDecimalString("-21598251");
    MUST_BE_TRUE(d.NChunks() == 1);
    MUST_BE_TRUE(d.ChunkAt(0) == 21598251);
    MUST_BE_TRUE(d.Sign() == false);
    
    auto e = BigInteger::CreateFromDecimalString("18446744073709551616");
    MUST_BE_TRUE(e.NChunks() == 2);
    MUST_BE_TRUE(e.ChunkAt(0) == 0);
    MUST_BE_TRUE(e.ChunkAt(1) == 1);
    MUST_BE_TRUE(e.Sign() == true);
    
    auto f = BigInteger::CreateFromDecimalString("-3456274718249612424124122");
    MUST_BE_TRUE(f == "-0x2dbe5072537be29a216da");
    
    auto g = "34562747182496124241241267209147917865398510196030563781650286532056182349860165325613059132";
    MUST_BE_TRUE(g == BigInteger::CreateFromHexString("0x10f798d283f1023ea25b9101fb81e7c96f9f23ba6297a4aa6a21033f03ceb3acf865aba5a4c3c"));
}

TEST_METHOD(Operator-)
{
    BigInteger a = "0b1010101";
    a = -a;
    
    MUST_BE_TRUE(a.ChunkAt(0) == 0b1010101);
    MUST_BE_TRUE(a.Sign() == false);
}

TEST_METHOD(Operator+)
{
    BigInteger a = "0b1010101";
    a = -a;
    a = +a;
    
    MUST_BE_TRUE(a.ChunkAt(0) == 0b1010101);
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(Addition_Positive_Positive)
{
    BigInteger a = "0xFFFFFFFFFFFF0000";
    ++a;
    a++;
    
    MUST_BE_TRUE(a == "0xFFFFFFFFFFFF0002");
            
    a += "0xFF8901FC8A83FC24FC";
    
    MUST_BE_TRUE(a.NChunks() == 2);
    MUST_BE_TRUE(a == "0x1008901FC8A83FB24FE");

    a = a + "0x111";
    
    MUST_BE_TRUE(a == "0x1008901FC8A83FB260F");
    
    BigInteger b = "0xFFFFFFFFFFFFFFFF";
    ++b;
    MUST_BE_TRUE(b.ChunkAt(0) == 0);
    MUST_BE_TRUE(b.ChunkAt(1) == 1);
}

TEST_METHOD(Addition_Negative_Negative)
{
    BigInteger a = "-0xFFFFFFFFFFFF0000";
    --a;
    a--;
    
    MUST_BE_TRUE(a == "-0xFFFFFFFFFFFF0002");
    
    a -= "0xFF8901FC8A83FC24FC";
    
    MUST_BE_TRUE(a.NChunks() == 2);
    MUST_BE_TRUE(a == "-0x1008901FC8A83FB24FE");

    a = a - "0x111";
    
    MUST_BE_TRUE(a == "-0x1008901FC8A83FB260F");
}

TEST_METHOD(Addition_Positive_Negative)
{
    BigInteger a = "0xFFFFFFFFFFFF0000F";
    a -= "0xF";
    
    MUST_BE_TRUE(a == "0xFFFFFFFFFFFF00000");
    MUST_BE_TRUE(a.NChunks() == 2);
    
    a -= "0xF0000000000000000";
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a == "0xFFFFFFFFFFF00000");
    
    BigInteger b = "0x1000000000000000";
    b = b - "0xFFFFFFFF";
    
    MUST_BE_TRUE(b == "0xFFFFFFF00000001");
    
    b += "-0xFFFFFFFFFFFFFFFFFFFFF1241412412414FDFcCFEAB2141414BCF";
    
    MUST_BE_TRUE(b == "-0xfffffffffffffffffffff1241412412414fdfbcfeab2241414bce");
    
    MUST_BE_TRUE( (b - b) == 0);
}

TEST_METHOD(Addition_Negative_Positive)
{
    BigInteger a = "-0xFFFFFFFFFFFF0000F";
    a += "0xF";
    
    MUST_BE_TRUE(a == "-0xFFFFFFFFFFFF00000");
    MUST_BE_TRUE(a.NChunks() == 2);
    
    a += "0xF0000000000000000";
    
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a == "-0xFFFFFFFFFFF00000");
    
    BigInteger b = "-0x1000000000000000";
    b = b + "0xFFFFFFFF";
    
    MUST_BE_TRUE(b == "-0xFFFFFFF00000001");
    
    b -= "-0xFFFFFFFFFFFFFFFFFFFFF1241412412414FDFcCFEAB2141414BCF";
    
    MUST_BE_TRUE(b == "0xfffffffffffffffffffff1241412412414fdfbcfeab2241414bce");
}

TEST_METHOD(Multiplication)
{
    BigInteger a = "0xfadf81";
    a *= 28831525;
    
    MUST_BE_TRUE(a == "0x1af1fa122bca5");
    
    a = a * "-0xfdf973187fc79789a98f987c914b10a04";
    MUST_BE_TRUE(a == "-0x1abb659d786c31536c994ecf6c7eb4e891391831fe6494");
    
    a *= 0;
    MUST_BE_TRUE(a == 0);
    
    MUST_BE_TRUE(-a == -1*a);
    
    a = "0x6547218481274f6875ac8675867db219678e9d6f8921";
    BigInteger b = "0x67214684ac8975987b659f8735d0987639e67869a6987c69b6";
    BigInteger c = a * b;
    MUST_BE_TRUE(c == "0x28ccc88d922526c367d975bf5b8838823f63c54ebdeaa18c68127cb8304c026d1e16e1d939ea15a3210dceb0860676");
}

TEST_METHOD(Division)
{
    BigInteger a = "0xfacd828fc8910abde";
    
    a /= 14214;
    MUST_BE_TRUE(a == "0x4845e21ed7ed91");
    
    a %= "0x1000";
    MUST_BE_TRUE(a == "0xd91");
    
    BigInteger b = "0x0afadf73faced768178f8719ca98763be9";
    auto resb = b.Divide("-0x23f13c89d89feab");
    
    MUST_BE_TRUE(resb.div == "-0x4e3480409010d23534e");
    MUST_BE_TRUE(resb.mod == "-0x1b285e0a587cd31");
    
    BigInteger c = "-0x12849f192649c6921ac986f9824ecba";
    auto resc = BigInteger::Divide(c, "0xdf7210a9074cde05");
    
    MUST_BE_TRUE(resc.div == "-0x15374bdfbd30df3");
    MUST_BE_TRUE(resc.mod == "0x70e45d1c22371305");
    
    BigInteger d = "-0x1240f024c0b3b738ac83ebd";
    auto resd = d.Divide("-0x27917428cba7387fbca");
    
    MUST_BE_TRUE(resd.div == "0x7619");
    MUST_BE_TRUE(resd.mod == "-0x7659ad8bfd94718c03");
}

TEST_METHOD(Division_Zero_Assert)
{
    BigInteger a = 124124;
    MUST_ASSERT(a / 0);
    MUST_ASSERT(a % 0);
    MUST_ASSERT(a.Divide("0x0"));
    MUST_ASSERT(BigInteger::Divide(a,"0b0"));
}

TEST_METHOD(Power)
{
    BigInteger one = 1;
    MUST_BE_TRUE(one.ToPower(1421) == 1);
    MUST_BE_TRUE((-one).ToPower(141) == -1);
    MUST_BE_TRUE((-one).ToPower(142) == 1);
    MUST_BE_TRUE(one.ToPower(0) == 1);
    MUST_BE_TRUE(BigInteger::Power(0, 13) == 0);
    
    BigInteger a = -2;
    a = a.ToPower(5);
    
    MUST_BE_TRUE(a == -32);
    
    a = BigInteger::Power(a, "0xad6");
    
    MUST_BE_TRUE(a == "0x400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    BigInteger b = "0xff85fac53dcbe5";
    b = b.ToPower("0b10110100");
    
    MUST_BE_TRUE(b == "0xb70b3c37d0a70cc4913409159eeff259eba5bb4e9fe914846c92e09e2706d926c52c06bc2593e97fafb94a65e9626506f0d4e12f38234bc5acb038adee38779aea47d2880f3221a308cc080169b2aa073b9d7f855cd3216dee858e8501eca3108eabd8e052d3ecbac53cc1c14491e1580ece9c3c26ef339845e9e1b3c2b540678895bc4592ecac3035b3de346b5ddf7f0014b98c0520732c36d3123add041248705cc489256c8f03890252c7964110882e34b2070d0ad05d5985024d75eb1f96cf5a66411013ebfd5a672dd42606fb3c24bdc1f9513459fc6fad1cb83f776518448d1df9663f7f8a943b68a980717b2e71eccbc59301bbbe8811243c81c8da3b9bcee7f50a8aaa28f42284c774e713c53d70e9b4c052d93d8d6e7ab07a29570e94e0df02d63e2f782657783c78def8816885ec34909d5a658bb8ecf33eb64f469118f121eec6063fceedd20f975d8b934c6601b1d9e8575d747a584b8f19b9ea58e9540110ce4469685b3baf7694e8212b86e78df3d75d576d27fb53adc805731de6427f8d4d5375d21a914710ad6d5aec976c33c6b584820cced3f34874e1f3b525d684163854d05a36b497ad215ef452facbe7fe9f821050a944e2d836d515487391a7e64483558a39e2d432fa24d40f69cf3aa2f5b7db8a9487f484afe2a4c02accf2a94a0eb6029378f1d10de815c6db778b77c1fc78731d3bf88029112bb9e8ce759bc73e2dc6ca6d30d4fe9b4e486c390700dff0944fa4bc361416da5d3f07a52f9c77c231033bbdb075f5f2d8cf055088830289bbe0a43608d2a747221a2885d414adff2f17f1335cfab2d4daa8da060f3ce9e9fe06fe9b9951bc70f1da49f4dbc40945696cff3c79b58125da1fca8c0c5bce3e0f1d2d3aa31403d737db891e0a79fc7296c6af12da85fc15a6693a60245a4dbacbcd7ee6f081843fa174277a98fde3d01b9f94a07a1fcc9b5d26f9f9a00ba0503f36e3919f99b9213de6710c5bf9d0e7f03fb9c4cc04f27c56ab2c71b1c46ac2dffd4a76a46830ffbbe84fbfab246ff3357c5ebee3685a4ec622d8ab75201f33851cc43bf8c5610b570c9f9a9d81c5d65eede8d7cc882ee0201466e296e21ed850ed8822bcd064649671fd36577ddd4f629e803478d9827c74da76555a15beb1422c8dc3dab1d7bac4941ec71f0802b3cf7daa31f4e25996c781d5516c29f3874cebd1c3d628ff818aec58d7d59459e33d04f006bfc2fc01dadd7cdf050e045d5585ffd199afd854967023b6d34146589ef2422bdd83562480de60e764555c536c2a807b651ce7278a9ae3be7a0b529c7faa6154f7d1b8262f8f03b11028a9af72edb9a0b0bac772fae303bafab8c234932055fb4d313833883679de1ad5842056711cc955b3e9a43002f1fb4f6ed1ea3091ad9eaca7267fef9761f6d6b922e206657523361f133aa35f6b56f56c9d41f8e63cc41ac12f308ae98cd22e2e62f20625ba0b0ef8ab72fa1df34654fafeaa9bfb1d8e1fe241b898feb1703fc52f0e9bc98273c91ea111ae3c883328cb52d2e30070279abcc228afa31226c1944c1cef171143f9901225fe7b9b4112ca82fda983e205560ea12d0621b856b05fa453104254c8acd649e7d3578117f6f25d83e03539792c9cd6ddf63e7dda2af1da25ba87b16424bb44f6b2b1b3c07c73de595c7f8ce9741c2c29cd7b64f63dea3da1f45270d9ad3d69f6fae6cb8f5519f2130c149e3e95959ae30ee1e3c97e0c0df27e4a823b25afdc2c7fb71543f845b9917500fb9731");
}

TEST_METHOD(Power_Negative_Assert)
{
    BigInteger a = 192412;
    
    MUST_ASSERT(a.ToPower(-1));
    MUST_ASSERT(a.ToPower("-0xff81"));
}

TEST_METHOD(Operator~)
{
    BigInteger a = "0b1010101010010101";
    BigInteger b = ~a;
    
    MUST_BE_TRUE(a.ChunkAt(0) + b.ChunkAt(0) == std::numeric_limits<u64>::max());
    MUST_BE_TRUE(b.Sign() == true);
    
    BigInteger c = "0b11110101011101001010101010101101011010101010101011010101010110010101101010101010101111110101010";
    c = -c;
    BigInteger d = ~c;

    MUST_BE_TRUE(d.NChunks() == 2);
    MUST_BE_TRUE(c.ChunkAt(0) + d.ChunkAt(0) == std::numeric_limits<u64>::max());
    MUST_BE_TRUE(c.ChunkAt(1) + d.ChunkAt(1) == std::numeric_limits<u64>::max());
    MUST_BE_TRUE(d.Sign() == false);
}

TEST_METHOD(Operator_Xor)
{
    BigInteger a = "0b110101";
    a ^= BigInteger::CreateFromBinaryString("0b11110101011");
    MUST_BE_TRUE(a == "0b11110011110");
    
    a ^= BigInteger::CreateFromBinaryString("0b11111110101110000101010111011001011010101010101010101001010101010101010011101010101");
                                                                                  
    
    MUST_BE_TRUE(a == "0b11111110101110000101010111011001011010101010101010101001010101010101010000011001011");
    
    a = a ^ -BigInteger::CreateFromBinaryString("0b010110");
    MUST_BE_TRUE(a == "0b11111110101110000101010111011001011010101010101010101001010101010101010000011011101");
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(Operator_And)
{
    BigInteger a = "0b1101011";
    a &= BigInteger::CreateFromBinaryString("0b101010111111");
    MUST_BE_TRUE(a == "0b101011");
    
    a = a & -BigInteger::CreateFromBinaryString("0b11111110101110000101010111011001011010101010101010101001010101010101010011101010101");
    MUST_BE_TRUE(a == "0b1");
    MUST_BE_TRUE(a.Sign() == true);
    
    BigInteger b = "0b11111110101110000101010111011001011010101010101010101001010101010101010011101010101";
    b &= BigInteger::CreateFromBinaryString("0b1111111");
    MUST_BE_TRUE(b == "0b1010101");
}

TEST_METHOD(Operator_Or)
{
    BigInteger a = "0b1010101111";
    a |= BigInteger::CreateFromBinaryString("0b11010111");
    MUST_BE_TRUE(a == "0b1011111111");
    
    a = a | -BigInteger::CreateFromBinaryString("0b11010101011010101010101011010101111110101010101011110101011010101010101100001011110");
    MUST_BE_TRUE(a == "0b11010101011010101010101011010101111110101010101011110101011010101010101101011111111");
     
    a |= -BigInteger::CreateFromBinaryString("0b111111111");
    MUST_BE_TRUE(a == "0b11010101011010101010101011010101111110101010101011110101011010101010101101111111111");
    MUST_BE_TRUE(a.Sign() == true);
}

TEST_METHOD(Operator_<<_>>)
{
    BigInteger a = "0b11011";
    a <<= 4;
    MUST_BE_TRUE(a == "0b110110000");
    
    a = a << 55;
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a == "0b1101100000000000000000000000000000000000000000000000000000000000");
                                           
    a = a << 1;
    MUST_BE_TRUE(a.NChunks() == 2);
    MUST_BE_TRUE(a.ChunkAt(1) == 1);
    MUST_BE_TRUE(a == "0b11011000000000000000000000000000000000000000000000000000000000000");
    
    a >>= 1;
    MUST_BE_TRUE(a.NChunks() == 1);
    MUST_BE_TRUE(a == "0b1101100000000000000000000000000000000000000000000000000000000000");
    
    a = a >> 58;
    MUST_BE_TRUE(a == "0b110110");
}

TEST_METHOD(Compare_Positive_Different_Size)
{
    auto a = BigInteger::CreateWithNChunks(2);
    auto b = BigInteger::CreateWithNChunks(5);
    auto c = BigInteger::CreateWithNChunks(7);
    
    MUST_BE_TRUE(a.CompareWith(a) == BigInteger::Equal);
    MUST_BE_TRUE(a.CompareWith(b) == BigInteger::Less);
    MUST_BE_TRUE(a.CompareWith(c) == BigInteger::Less);
    
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Greater);
    MUST_BE_TRUE(BigInteger::Compare(b, b) == BigInteger::Equal);
    MUST_BE_TRUE(BigInteger::Compare(b, c) == BigInteger::Less);
    
    MUST_BE_TRUE(BigInteger::Compare(c, a) == BigInteger::Greater);
    MUST_BE_TRUE(BigInteger::Compare(c, b) == BigInteger::Greater);
    MUST_BE_TRUE(BigInteger::Compare(c, c) == BigInteger::Equal);
}

TEST_METHOD(Compare_Positive_Same_Size_One_Chunk)
{
    BigInteger a = "0x41FA3";
    BigInteger b = "0xFF1523";
    
    MUST_BE_TRUE(BigInteger::Compare(a, b) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Greater);
    MUST_BE_TRUE(BigInteger::Compare(a, a) == BigInteger::Equal);
    MUST_BE_TRUE(BigInteger::Compare(b, b) == BigInteger::Equal);
}

TEST_METHOD(Compare_Positive_Same_Size_Several_Chunks)
{
    auto a = BigInteger::CreateWithNChunks(2);
    a.ChunkAt(0) = 298251;
    a.ChunkAt(1) = 2978195;
    
    auto b = BigInteger::CreateWithNChunks(2);
    b.ChunkAt(0) = 10;
    b.ChunkAt(1) = 2978195;
    
    MUST_BE_TRUE(BigInteger::Compare(a, b) == BigInteger::Greater);
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Less);
}

TEST_METHOD(Compare_Negative_Different_Size)
{
    auto a = BigInteger::CreateWithNChunks(2);
    auto b = -BigInteger::CreateWithNChunks(5);
    auto c = -BigInteger::CreateWithNChunks(7);
    
    MUST_BE_TRUE(a.CompareWith(a) == BigInteger::Equal);
    MUST_BE_TRUE(a.CompareWith(b) == BigInteger::Greater);
    MUST_BE_TRUE(a.CompareWith(c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(b, b) == BigInteger::Equal);
    MUST_BE_TRUE(BigInteger::Compare(b, c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(c, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, b) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, c) == BigInteger::Equal);
}

TEST_METHOD(Compare_Negative_Same_Size_One_Chunk)
{
    BigInteger a = 12525;
    BigInteger b = -25982;
    BigInteger c = -284129;
    
    MUST_BE_TRUE(a.CompareWith(a) == BigInteger::Equal);
    MUST_BE_TRUE(a.CompareWith(b) == BigInteger::Greater);
    MUST_BE_TRUE(a.CompareWith(c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(b, b) == BigInteger::Equal);
    MUST_BE_TRUE(BigInteger::Compare(b, c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(c, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, b) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, c) == BigInteger::Equal);
}

TEST_METHOD(Compare_Negative_Same_Size_Several_Chunks)
{
    BigInteger a = BigInteger::CreateWithNChunks(2);
    a.ChunkAt(0) = 21525;
    a.ChunkAt(1) = 525;
    
    BigInteger b = -BigInteger::CreateWithNChunks(2);
    b.ChunkAt(0) = 12;
    b.ChunkAt(1) = 100;
    
    BigInteger c = -BigInteger::CreateWithNChunks(2);
    c.ChunkAt(0) = 13;
    c.ChunkAt(1) = 100;
    
    MUST_BE_TRUE(a.CompareWith(a) == BigInteger::Equal);
    MUST_BE_TRUE(a.CompareWith(b) == BigInteger::Greater);
    MUST_BE_TRUE(a.CompareWith(c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(b, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(b, b) == BigInteger::Equal);
    MUST_BE_TRUE(BigInteger::Compare(b, c) == BigInteger::Greater);
    
    MUST_BE_TRUE(BigInteger::Compare(c, a) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, b) == BigInteger::Less);
    MUST_BE_TRUE(BigInteger::Compare(c, c) == BigInteger::Equal);
}

TEST_METHOD(ToBinaryString)
{
    BigInteger a = "0b10100101010";
    MUST_BE_TRUE(a.ToBinaryString() == "0b10100101010");
    
    BigInteger b = "0b1010101010101010101010";
    b = -b;
    MUST_BE_TRUE(b.ToBinaryString() == "-0b1010101010101010101010");
    
    BigInteger c = "0b0001010110010001011110111110101010010101101010101001101011111010101001010101010101010101";
    MUST_BE_TRUE(c.ToBinaryString() == "0b1010110010001011110111110101010010101101010101001101011111010101001010101010101010101");
    
    BigInteger d = "0b000001011010010101010001011111101011010101010101100101010101011011010010101011011001010101110011";
    d = -d;
    MUST_BE_TRUE(d.ToBinaryString() == "-0b1011010010101010001011111101011010101010101100101010101011011010010101011011001010101110011");
    
    BigInteger e = "-0";
    MUST_BE_TRUE(e.ToBinaryString() == "0b0");
}

TEST_METHOD(ToHexString)
{
    BigInteger a = "0xF89FCD110A";
    MUST_BE_TRUE(a.ToHexString() == "0xF89FCD110A");
    
    BigInteger b = "0x1CA39E0A";
    b = -b;
    MUST_BE_TRUE(b.ToHexString() == "-0x1CA39E0A");
    
    BigInteger c = "0x00000FA748CE721950ABCDEF84915DCB";
    MUST_BE_TRUE(c.ToHexString() == "0xFA748CE721950ABCDEF84915DCB");
    
    BigInteger d = "0x0000000000000000000000000ABCDBFF85789187925981285125002410082140280415012CBAFD8951025BDACEF315CD82";
    d = -d;
    MUST_BE_TRUE(d.ToHexString() == "-0xABCDBFF85789187925981285125002410082140280415012CBAFD8951025BDACEF315CD82");
    
    BigInteger e = "-0";
    MUST_BE_TRUE(e.ToHexString() == "0x0");
}

TEST_METHOD(GetDecimalString)
{
    BigInteger a = "64712414";
    MUST_BE_TRUE(a.ToDecimalString() == "64712414");
    
    BigInteger b = "26741298421";
    b = -b;
    MUST_BE_TRUE(b.ToDecimalString() == "-26741298421");
    
    BigInteger c = "000000000000153586359163966936891689685135";
    MUST_BE_TRUE(c.ToDecimalString() == "153586359163966936891689685135");
    
    BigInteger d = "-0";
    MUST_BE_TRUE(d.ToDecimalString() == "0");
    
    BigInteger e = "000000000000241849125912657812658791265897123128412491264127649182412";
    MUST_BE_TRUE(e.ToDecimalString() == "241849125912657812658791265897123128412491264127649182412");
}

TEST_CLASS_END(BigIntegerTest)
}
#endif

