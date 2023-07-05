#ifndef Array_hpp
#define Array_hpp

#include "Assert.hpp"
#include "IntTypes.hpp"
#include <algorithm>

namespace AmvilinaCore{

template <class Tdata, class Allocator = std::allocator<Tdata>>
class Array{
protected:
    Tdata* _data;
    u64 _size;
    u64 _capacity;
    Allocator _allocator;
    static constexpr u8 APPEND_FACTOR = 2;
public:
    Array();
    explicit Array(u64 size);
    Array(const Array& other);
    Array& operator=(const Array& other);
    Array(Array&& other);
    Array& operator=(Array&& other);
    Array(std::initializer_list<Tdata> list);
    ~Array();
    
    static Array CreateWithSize(u64 size);
    static Array CreateWithCapacity(u64 capacity);
    static Array CreateWithSizeAndCapacity(u64 size, u64 capacity);
    
    u64 Size() const;
    u64 Capacity() const;
    Tdata* Data();
    const Tdata* Data() const;
    const Tdata& operator[](u64 index) const;
    Tdata& operator[](u64 index);
    const Tdata& At(u64 index) const;
    Tdata& At(u64 index);
    
    void Resize(u64 value);
    void Reserve(u64 value);
    void ShrinkToFit();
    Array& Append(const Tdata& data);
    Array& Append(const Array& other);
private:
    void AllocateMemory(u64 size);
    void FreeMemory();
    void CopyFrom(const Array& other);
    void MoveFrom(Array&& other);
    void CopyToTheEndFrom(const Array& other);
public:
    template <class Tpointer, class Treference>
    class TemplateIterator;
    
    using Iterator      = TemplateIterator<Tdata*, Tdata&>;
    using ConstIterator = TemplateIterator<const Tdata*, const Tdata&>;
    
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;
};

#include "ArrayIterator.hpp"
#include "ArrayImplementation.hpp"

}
#endif
