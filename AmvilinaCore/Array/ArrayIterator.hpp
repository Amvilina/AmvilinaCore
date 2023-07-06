#ifndef ArrayIterator_hpp
#define ArrayIterator_hpp

template <class Tdata>
template <class Tpointer, class Treference>
class Array<Tdata>::TemplateIterator {
public:
    using iterator_category = std::contiguous_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Tdata;
    using pointer           = Tpointer;
    using reference         = Treference;
private:
    pointer _ptr;
public:
    TemplateIterator(pointer ptr) {
        _ptr = ptr;
    }
    
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
