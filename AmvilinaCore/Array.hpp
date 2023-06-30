#ifndef Array_hpp
#define Array_hpp

#include "Assert.hpp"

template <class Tdata, class Allocator = std::allocator<Tdata>>
class Array{
private:
    using u64 = uint64_t;
    
    Tdata* _data;
    u64 _size;
    Allocator _allocator;
public:
    Array() : _data(nullptr), _size(0) {}
    
    explicit Array(u64 size) {
        AllocateMemory(size);
    }
    
    Array(const Array& other) {
        AllocateMemory(other.Size());
        CopyFrom(other);
    }
    
    Array& operator=(const Array& other) {
        if(this == &other)
            return *this;
        
        if(Size() != other.Size()) {
            FreeMemory();
            AllocateMemory(other.Size());
        }
        
        CopyFrom(other);
        
        return *this;
    }
    
    Array(Array&& other) {
        MoveFrom(std::move(other));
    }
    
    Array& operator=(Array&& other) {
        if(this == &other)
            return *this;
        
        FreeMemory();
        MoveFrom(std::move(other));
        
        return *this;
    }
    
    Array(std::initializer_list<Tdata> list) {
        AllocateMemory(list.size());
        
        const Tdata* listPtr = list.begin();
        const Tdata* listEnd = list.end();
        Tdata* thisPtr = &_data[0];
        
        while(listPtr != listEnd) {
            *thisPtr = *listPtr;
            ++thisPtr;
            ++listPtr;
        }
    }
    
    ~Array() {
        FreeMemory();
    }
    
    u64 Size() const{
        return _size;
    }
    
    Tdata* Data() {
        return _data;
    }
    
    const Tdata* Data() const {
        return _data;
    }
    
    Tdata operator[](u64 index) const {
        return At(index);
    }
    
    Tdata& operator[](u64 index) {
        return At(index);
    }
    
    Tdata At(u64 index) const {
        ASSERT(index >= 0 && index < Size());
        return _data[index];
    }
    
    Tdata& At(u64 index) {
        ASSERT(index >= 0 && index < Size());
        return _data[index];
    }
private:
    void AllocateMemory(u64 size){
        ASSERT(size > 0);
        _size = size;
        _data = _allocator.allocate(_size);
    }
    
    void FreeMemory() {
        _allocator.deallocate(_data, _size);
    }
    
    void CopyFrom(const Array& other) {
        ASSERT(Size() == other.Size());
        
        Tdata* thisPtr = &_data[0];
        Tdata* endPtr = &_data[Size()];
        const Tdata* otherPtr = &other._data[0];
        
        while(thisPtr != endPtr) {
            *thisPtr = *otherPtr;
            ++thisPtr;
            ++otherPtr;
        }
    }
    
    void MoveFrom(Array&& other) {
        _data = other._data;
        _size = other._size;
        
        other._data = nullptr;
        other._size = 0;
    }
public:
    template <class Tpointer, class Treference>
    class TemplateIterator;
    
    using Iterator      = TemplateIterator<Tdata*, Tdata&>;
    using ConstIterator = TemplateIterator<const Tdata*, const Tdata&>;
    
    Iterator begin() {
        if(Size() == 0)
            return Iterator(nullptr);
        return Iterator(Data());
    }
    
    Iterator end() {
        if(Size() == 0)
            return Iterator(nullptr);
        return Iterator(Data() + Size());
    }
    
    ConstIterator begin() const{
        return cbegin();
    }
    
    ConstIterator end() const{
        return cend();
    }
    
    ConstIterator cbegin() const{
        if(Size() == 0)
            return ConstIterator(nullptr);
        return ConstIterator(Data());
    }
    
    ConstIterator cend() const{
        if(Size() == 0)
            return ConstIterator(nullptr);
        return ConstIterator(Data() + Size());
    }
};

template <class Tdata, class Allocator>
template <class Tpointer, class Treference>
class Array<Tdata, Allocator>::TemplateIterator {
public:
    using iterator_category = std::contiguous_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Tdata;
    using pointer           = Tpointer;
    using reference         = Treference;
private:
    pointer _ptr;
public:
    TemplateIterator(pointer ptr) : _ptr(ptr) {}
    
    pointer RawPointer() const {
        return _ptr;
    }
    
    reference operator*() const {
        return *_ptr;
    }
    
    pointer operator->() const {
        return _ptr;
    }
    
    TemplateIterator& operator++() {
        ++_ptr;
        return *this;
    }
    
    TemplateIterator operator++(int) {
        TemplateIterator it = *this;
        ++_ptr;
        return it;
    }
    
    TemplateIterator& operator--() {
        --_ptr;
        return *this;
    }
    
    TemplateIterator operator--(int) {
        TemplateIterator it = *this;
        --_ptr;
        return it;
    }
    
    friend bool operator==(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr == b._ptr;
    }
    
    friend bool operator!=(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr != b._ptr;
    }
    
    friend bool operator>(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr > b._ptr;
    }
    
    friend bool operator<(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr < b._ptr;
    }
    
    friend bool operator>=(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr >= b._ptr;
    }
    
    friend bool operator<=(const TemplateIterator& a, const TemplateIterator& b) {
        return a._ptr <= b._ptr;
    }
    
    friend TemplateIterator operator+(difference_type n, const TemplateIterator& it) {
        TemplateIterator temp = it;
        return temp += n;
    }
    
    friend TemplateIterator operator+(const TemplateIterator& it, difference_type n) {
        TemplateIterator temp = it;
        return temp += n;
    }
    
    TemplateIterator& operator+=(difference_type n) {
        _ptr += n;
        return *this;
    }
    
    TemplateIterator operator-(difference_type n) const {
        TemplateIterator temp = *this;
        return temp -= n;
    }
    
    TemplateIterator& operator-=(difference_type n) {
        return (*this) += -n;
    }
    
    reference operator[](difference_type n) const {
        return *(_ptr + n);
    }
    
    difference_type operator-(const TemplateIterator& other) const {
        return _ptr - other._ptr;
    }
};

#endif
