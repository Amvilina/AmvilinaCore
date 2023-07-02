#ifndef ArrayTests_hpp
#define ArrayTests_hpp

#include "TestClass.hpp"
#include "Array.hpp"

namespace ArrayTests{

using ArrayForMemoryTest = Array<int, UnitTests::TestAllocator<int>>;

TEST_CLASS_BEGIN(ArrayTest)

TEST_METHOD(Default_Constructor_Size_Function_Capacity_Function)
{
    Array<int> a;
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
}

TEST_METHOD(Size_Constructor_Size_Function_Capacity_Function)
{
    Array<int> a(3);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 3);
}

TEST_METHOD(At_And_Operator_Brackets_In_Range)
{
    Array<int> a(2);
    a.At(0) = 1;
    a[1] = 2;
    
    MUST_BE_TRUE(a[0] == 1);
    MUST_BE_TRUE(a.At(1) == 2);
}

TEST_METHOD(At_And_Operator_Brackets_Out_Of_Range_Assert)
{
    Array<int> a(2);
    
    MUST_ASSERT(a[-1]);
    MUST_ASSERT(a[2]);
    MUST_ASSERT(a.At(-1));
    MUST_ASSERT(a.At(2));
}


TEST_METHOD(Initializer_List_Constructor_Not_Zero_Elements)
{
    Array<int> a = { 5, 7 };
    
    MUST_BE_TRUE(a.Size() == 2);
    MUST_BE_TRUE(a.Capacity() == 2);
    MUST_BE_TRUE(a[0] == 5);
    MUST_BE_TRUE(a[1] == 7);
}

TEST_METHOD(Initializer_List_Constructor_Zero_Elements)
{
    Array<int> a = { };
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
}

TEST_METHOD(Copy_Construstor)
{
    Array<int> a = { 4, 8 };
    Array<int> b = a;
    
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Copy_Assignment_Same_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(2);
    b = a;
    
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Copy_Assignment_Smaller_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(3);
    b = a;
    
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 3);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Copy_Assignment_Bigger_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(1);
    b = a;
    
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Copy_Assignment_Self)
{
    Array<int> a = { 4, 8 };
    a = a;
    
    MUST_BE_TRUE(a.Size() == 2);
    MUST_BE_TRUE(a.Capacity() == 2);
    MUST_BE_TRUE(a[0] == 4);
    MUST_BE_TRUE(a[1] == 8);
}

TEST_METHOD(Move_Construstor)
{
    Array<int> a = { 4, 8 };
    Array<int> b = std::move(a);
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Move_Assignment_Same_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(2);
    b = std::move(a);
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Move_Assignment_Bigger_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(1);
    b = std::move(a);
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Move_Assignment_Smaller_Size)
{
    Array<int> a = { 4, 8 };
    Array<int> b(3);
    b = std::move(a);
    
    MUST_BE_TRUE(a.Size() == 0);
    MUST_BE_TRUE(a.Capacity() == 0);
    MUST_BE_TRUE(b.Size() == 2);
    MUST_BE_TRUE(b.Capacity() == 2);
    MUST_BE_TRUE(b[0] == 4);
    MUST_BE_TRUE(b[1] == 8);
}

TEST_METHOD(Move_Assignment_Self)
{
    Array<int> a = { 4, 8 };
    a = std::move(a);
    
    MUST_BE_TRUE(a.Size() == 2);
    MUST_BE_TRUE(a.Capacity() == 2);
    MUST_BE_TRUE(a[0] == 4);
    MUST_BE_TRUE(a[1] == 8);
}

TEST_METHOD(Data_Function)
{
    Array<int> a = { 10, 12 };
    int* data = a.Data();
    
    MUST_BE_TRUE(data == &a[0]);
    
    const Array<int> b = { 1, 2 };
    const int* cdata = b.Data();
    
    MUST_BE_TRUE(*cdata == 1);
    MUST_BE_TRUE(*(cdata+1) == 2);
}

TEST_METHOD(Reserve_Function_Bigger_Value)
{
    Array<int> a = { 1, 2, 3 };
    a.Reserve(5);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 5);
}

TEST_METHOD(Reserve_Function_Same_Value)
{
    Array<int> a = { 1, 2, 3 };
    a.Reserve(3);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 3);
}

TEST_METHOD(Reserve_Function_Smaller_Value_Assert)
{
    Array<int> a = { 1, 2, 3 };
    MUST_ASSERT(a.Reserve(2));
}

TEST_METHOD(Append_Value_Size_Under_Capacity)
{
    Array<int> a = {2, 4};
    a.Reserve(3);
    
    a.Append(10);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 3);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 4);
    MUST_BE_TRUE(a[2] == 10);
}

TEST_METHOD(Append_Value_Size_Equal_Capacity)
{
    Array<int> a = {2, 4};
    
    a.Append(10);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 4);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 4);
    MUST_BE_TRUE(a[2] == 10);
}

TEST_METHOD(Append_Array_Capacity_Under)
{
    Array<int> a = {2};
    a.Reserve(4);
    Array<int> b = {4, 8};
    
    a.Append(b);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 4);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 4);
    MUST_BE_TRUE(a[2] == 8);
}

TEST_METHOD(Append_Array_Capacity_Equal)
{
    Array<int> a = {2};
    a.Reserve(3);
    Array<int> b = {4, 8};
    
    a.Append(b);
    
    MUST_BE_TRUE(a.Size() == 3);
    MUST_BE_TRUE(a.Capacity() == 3);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 4);
    MUST_BE_TRUE(a[2] == 8);
}

TEST_METHOD(Append_Array_Capacity_Over_First_Is_Bigger)
{
    Array<int> a = {2, 3};
    a.Reserve(3);
    Array<int> b = {4, 8};
    
    a.Append(b);
    
    MUST_BE_TRUE(a.Size() == 4);
    MUST_BE_TRUE(a.Capacity() == 6);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 3);
    MUST_BE_TRUE(a[2] == 4);
    MUST_BE_TRUE(a[3] == 8);
}

TEST_METHOD(Append_Array_Capacity_Over_Second_Is_Bigger)
{
    Array<int> a = {2};
    a.Reserve(2);
    Array<int> b = {4, 8, 11};
    
    a.Append(b);
    
    MUST_BE_TRUE(a.Size() == 4);
    MUST_BE_TRUE(a.Capacity() == 6);
    MUST_BE_TRUE(a[0] == 2);
    MUST_BE_TRUE(a[1] == 4);
    MUST_BE_TRUE(a[2] == 8);
    MUST_BE_TRUE(a[3] == 11);
}

TEST_METHOD(Destructor_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b = {3, 4};
}

TEST_METHOD(Copy_Constructor_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b(a);
}

TEST_METHOD(Copy_Assignment_Same_Size_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b(5);
    
    b = a;
}

TEST_METHOD(Copy_Assignment_Different_Size_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b(3);
    ArrayForMemoryTest c(8);
    
    b = a;
    c = a;
}

TEST_METHOD(Move_Constructor_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b = std::move(a);
}

TEST_METHOD(Move_Assignment_Same_Size_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b(5);
    
    b = std::move(a);
}

TEST_METHOD(Move_Assignment_Different_Size_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    ArrayForMemoryTest b(3);
    ArrayForMemoryTest c(8);
    
    b = std::move(a);
    c = std::move(b);
}

TEST_METHOD(Self_Assignment_No_Memory_Leaks)
{
    ArrayForMemoryTest a(5);
    
    a = a;
    a = std::move(a);
}

TEST_METHOD(Reserve_No_Memory_Leaks)
{
    ArrayForMemoryTest a(3);
    
    a.Reserve(3);
    a.Reserve(5);
}

TEST_METHOD(Append_Value_No_Memory_Leaks)
{
    ArrayForMemoryTest a(2);
    
    a.Append(2);
    a.Append(4);
    a.Append(82);
}

TEST_METHOD(Append_Array_No_Memory_Leaks)
{
    ArrayForMemoryTest a(3);
    ArrayForMemoryTest b(2);
    
    a.Append(b);
    a.Append(b);
    a.Append(b);
}

TEST_METHOD(Begin_End_Return_Valid_Iterators)
{
    Array<int> a(3);
    auto itb = a.begin();
    auto ite = a.end();
    auto itcb = a.cbegin();
    auto itce = a.cend();

    MUST_BE_TRUE(itb.RawPointer() == a.Data());
    MUST_BE_TRUE(ite.RawPointer() == a.Data() + 3);
    MUST_BE_TRUE(itcb.RawPointer() == a.Data());
    MUST_BE_TRUE(itce.RawPointer() == a.Data() + 3);
}

TEST_METHOD(Begin_End_Empty_Array_Return_Nullptr_Iterator)
{
    Array<int> a;
    auto itb = a.begin();
    auto ite = a.end();
    auto itcb = a.cbegin();
    auto itce = a.cend();
    
    MUST_BE_TRUE(itb.RawPointer() == nullptr);
    MUST_BE_TRUE(ite.RawPointer() == nullptr);
    MUST_BE_TRUE(itcb.RawPointer() == nullptr);
    MUST_BE_TRUE(itce.RawPointer() == nullptr);
}

TEST_METHOD(Iterator_Operator_Asterisk)
{
    Array<int> a = {7};
    auto it = a.begin();
    
    MUST_BE_TRUE(*it == 7);
}

TEST_METHOD(Iterator_Operator_Arrow)
{
    struct Arrow{
        int GetValue() const {return 11;}
    };
    
    Array<Arrow> a(1);
    auto it = a.begin();
    
    MUST_BE_TRUE(it->GetValue() == 11);
}

TEST_METHOD(Iterator_Increment)
{
    Array<int> a = {1, 2, 3};
    auto it = a.begin();
    
    MUST_BE_TRUE(*it == 1);
    ++it;
    MUST_BE_TRUE(*it == 2);
    MUST_BE_TRUE(*(it++) == 2);
    MUST_BE_TRUE(*it == 3);
}

TEST_METHOD(Iterator_Decrement)
{
    Array<int> a = {1, 2, 3};
    auto it = a.end();
    --it;
    
    MUST_BE_TRUE(*it == 3);
    MUST_BE_TRUE(*(it--) == 3);
    MUST_BE_TRUE(*it == 2);
}

TEST_METHOD(Iterator_Compare)
{
    Array<int> a = {1, 2};
    auto it1 = a.begin();
    auto it2 = ++a.begin();
    
    MUST_BE_TRUE(it1 != it2);
    MUST_BE_FALSE(it1 == it2);
    MUST_BE_TRUE(it1 < it2);
    MUST_BE_TRUE(it1 <= it2);
    MUST_BE_FALSE(it1 > it2);
    MUST_BE_FALSE(it1 >= it2);
    
    ++it1;
    
    MUST_BE_FALSE(it1 != it2);
    MUST_BE_TRUE(it1 == it2);
    MUST_BE_FALSE(it1 < it2);
    MUST_BE_TRUE(it1 <= it2);
    MUST_BE_FALSE(it1 > it2);
    MUST_BE_TRUE(it1 >= it2);
    
    --it2;
    
    MUST_BE_TRUE(it1 != it2);
    MUST_BE_FALSE(it1 == it2);
    MUST_BE_FALSE(it1 < it2);
    MUST_BE_FALSE(it1 <= it2);
    MUST_BE_TRUE(it1 > it2);
    MUST_BE_TRUE(it1 >= it2);
}

TEST_METHOD(Iterator_Operator_Plus)
{
    Array<int> a = {1, 2, 3, 4, 5};
    auto it = a.begin();
    
    it = it + 1;
    MUST_BE_TRUE(*it == 2);
    
    it += 3;
    MUST_BE_TRUE(*it == 5);
    
    it = it + (-2);
    MUST_BE_TRUE(*it == 3);
    
    it += -2;
    MUST_BE_TRUE(*it == 1);
    
    it = 4 + it;
    MUST_BE_TRUE(*it == 5);
    
    it = -3 + it;
    MUST_BE_TRUE(*it == 2);
}

TEST_METHOD(Iterator_Operator_Minus)
{
    Array<int> a = {1, 2, 3, 4, 5};
    auto it = a.end();
    
    it = it - 2;
    MUST_BE_TRUE(*it == 4);
    
    it -= 3;
    MUST_BE_TRUE(*it == 1);
    
    it = it - (-2);
    MUST_BE_TRUE(*it == 3);
    
    it -= -2;
    MUST_BE_TRUE(*it == 5);
}

TEST_METHOD(Iterator_Operator_Brackets)
{
    Array<int> a = {1, 2, 3, 4, 5};
    auto it = a.begin();
    
    MUST_BE_TRUE(it[0] == 1);
    MUST_BE_TRUE(it[2] == 3);
    
    it += 2;
    MUST_BE_TRUE(*it == 3);
    MUST_BE_TRUE(it[-1] == 2);
    MUST_BE_TRUE(it[-2] == 1);
}

TEST_METHOD(Iterator_Operator_Difference)
{
    Array<int> a(4);
    
    MUST_BE_TRUE((a.end() - a.begin()) == 4);
}

TEST_CLASS_END(ArrayTest)

}
#endif

