#ifndef ArrayImplementation_h
#define ArrayImplementation_h

#define ARRAY_TEMPLATE template <class Tdata, class Allocator>
#define ARRAY_CLASS Array<Tdata, Allocator>
#define ARRAY_TYPENAME typename ARRAY_CLASS

ARRAY_TEMPLATE
ARRAY_CLASS::Array() : _data(nullptr), _size(0), _capacity(0) {}

ARRAY_TEMPLATE
ARRAY_CLASS::Array(u64 size) {
    AllocateMemory(size);
    _size = size;
}

ARRAY_TEMPLATE
ARRAY_CLASS::Array(const Array& other) {
    AllocateMemory(other.Size());
    CopyFrom(other);
}

ARRAY_TEMPLATE
ARRAY_CLASS& ARRAY_CLASS::operator=(const Array& other) {
    if(this == &other)
        return *this;
    
    if(Capacity() < other.Size()) {
        FreeMemory();
        AllocateMemory(other.Size());
    }
    
    CopyFrom(other);
    
    return *this;
}

ARRAY_TEMPLATE
ARRAY_CLASS::Array(Array&& other) {
    MoveFrom(std::move(other));
}

ARRAY_TEMPLATE
ARRAY_CLASS& ARRAY_CLASS::operator=(Array&& other) {
    if(this == &other)
        return *this;
    
    FreeMemory();
    MoveFrom(std::move(other));
    
    return *this;
}

ARRAY_TEMPLATE
ARRAY_CLASS::Array(std::initializer_list<Tdata> list) {
    AllocateMemory(list.size());
    _size = list.size();
    
    const Tdata* listPtr = list.begin();
    const Tdata* listEnd = list.end();
    Tdata* thisPtr = &_data[0];
    
    while(listPtr != listEnd) {
        *thisPtr = *listPtr;
        ++thisPtr;
        ++listPtr;
    }
}

ARRAY_TEMPLATE
ARRAY_CLASS::~Array() {
    FreeMemory();
}

ARRAY_TEMPLATE
ARRAY_CLASS ARRAY_CLASS::CreateWithSize(u64 size) {
    return Array(size);
}

ARRAY_TEMPLATE
ARRAY_CLASS ARRAY_CLASS::CreateWithCapacity(u64 capacity) {
    return CreateWithSizeAndCapacity(0, capacity);
}

ARRAY_TEMPLATE
ARRAY_CLASS ARRAY_CLASS::CreateWithSizeAndCapacity(u64 size, u64 capacity) {
    ASSERT(capacity >= size);
    Array arr(capacity);
    arr._size = size;
    return arr;
}

ARRAY_TEMPLATE
u64 ARRAY_CLASS::Size() const {
    return _size;
}

ARRAY_TEMPLATE
u64 ARRAY_CLASS::Capacity() const {
    return _capacity;
}

ARRAY_TEMPLATE
Tdata* ARRAY_CLASS::Data() {
    return _data;
}

ARRAY_TEMPLATE
const Tdata* ARRAY_CLASS::Data() const {
    return _data;
}

ARRAY_TEMPLATE
const Tdata& ARRAY_CLASS::operator[](u64 index) const {
    return At(index);
}

ARRAY_TEMPLATE
Tdata& ARRAY_CLASS::operator[](u64 index) {
    return At(index);
}

ARRAY_TEMPLATE
const Tdata& ARRAY_CLASS::At(u64 index) const {
    ASSERT(index >= 0 && index < Size());
    return _data[index];
}

ARRAY_TEMPLATE
Tdata& ARRAY_CLASS::At(u64 index) {
    ASSERT(index >= 0 && index < Size());
    return _data[index];
}

ARRAY_TEMPLATE
void ARRAY_CLASS::ShrinkToFit() {
    if(Capacity() == Size())
        return;
    Array temp = *this;
    *this = temp;
}

ARRAY_TEMPLATE
void ARRAY_CLASS::Resize(u64 value) {
    if(value > Capacity())
        Reserve(value);
    _size = value;
}

ARRAY_TEMPLATE
void ARRAY_CLASS::Reserve(u64 value) {
    ASSERT(value >= Capacity());
    
    if(value == Capacity())
        return;
    
    Array copy = *this;
    FreeMemory();
    
    AllocateMemory(value);
    CopyFrom(copy);
}

ARRAY_TEMPLATE
ARRAY_CLASS& ARRAY_CLASS::Append(const Tdata& data) {
    if(Size() == Capacity())
        Reserve(Capacity() * APPEND_FACTOR);
    ++_size;
    At(Size() - 1) = data;
    return *this;
}

ARRAY_TEMPLATE
ARRAY_CLASS& ARRAY_CLASS::Append(const Array& other) {
    if(Size() + other.Size() > Capacity())
    {
        Array temp = *this;
        Reserve(std::max(Size(), other.Size()) * APPEND_FACTOR);
        CopyFrom(temp);
    }
    
    CopyToTheEndFrom(other);
    return *this;
}

ARRAY_TEMPLATE
void ARRAY_CLASS::AllocateMemory(u64 capacity){
    ASSERT(capacity > 0);
    _capacity = capacity;
    _data = _allocator.allocate(_capacity);
}

ARRAY_TEMPLATE
void ARRAY_CLASS::FreeMemory() {
    _allocator.deallocate(_data, _capacity);
}

ARRAY_TEMPLATE
void ARRAY_CLASS::CopyFrom(const Array& other) {
    ASSERT(Capacity() >= other.Size());
    
    Tdata* thisPtr = &_data[0];
    const Tdata* endPtr = &other._data[other.Size()];
    const Tdata* otherPtr = &other._data[0];
    
    while(otherPtr != endPtr) {
        *thisPtr = *otherPtr;
        ++thisPtr;
        ++otherPtr;
    }
    
    _size = other.Size();
}

ARRAY_TEMPLATE
void ARRAY_CLASS::CopyToTheEndFrom(const Array& other) {
    ASSERT(Size() + other.Size() <= Capacity());
    
    Tdata* thisPtr = &_data[Size()];
    Tdata* otherPtr = &other._data[0];
    Tdata* endPtr = &other._data[other.Size()];
    
    while (otherPtr != endPtr) {
        *thisPtr = *otherPtr;
        ++thisPtr;
        ++otherPtr;
    }
    
    _size += other.Size();
}

ARRAY_TEMPLATE
void ARRAY_CLASS::MoveFrom(Array&& other) {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::Iterator ARRAY_CLASS::begin() {
    if(Size() == 0)
        return Iterator(nullptr);
    return Iterator(Data());
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::Iterator ARRAY_CLASS::end() {
    if(Size() == 0)
        return Iterator(nullptr);
    return Iterator(Data() + Size());
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::ConstIterator ARRAY_CLASS::begin() const{
    return cbegin();
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::ConstIterator ARRAY_CLASS::end() const{
    return cend();
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::ConstIterator ARRAY_CLASS::cbegin() const{
    if(Size() == 0)
        return ConstIterator(nullptr);
    return ConstIterator(Data());
}

ARRAY_TEMPLATE
ARRAY_TYPENAME::ConstIterator ARRAY_CLASS::cend() const{
    if(Size() == 0)
        return ConstIterator(nullptr);
    return ConstIterator(Data() + Size());
}

#endif
