#ifndef BUFFER
#define BUFFER

#include <iostream>
#include <cstdlib>

namespace my {

template<class elem_t>
class buffer {

private:
    size_t size_     = 0;
    size_t capacity_ = 0;
    elem_t* data_  = nullptr;

public: 
    
    buffer(size_t capacity) noexcept {
        std::cout << "ctor. create buffer\n";
        if (capacity <= 0) {
            std::abort(); 
        }
        capacity_ = capacity; 
        data_ = new elem_t[capacity_]; 
    }

    buffer() = default;

    buffer(const buffer& other) noexcept {  // copy ctor
        std::cout << "copy ctor\n";
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new elem_t[capacity_];
        for (int i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
        // std::strcpy(data_, other.data_);
    }

    buffer(const buffer&& other) noexcept {  // move ctor
        std::cout << "move ctor\n";
        data_ = other.data_;
        other.data_ = nullptr;
    }

    buffer& operator=(const buffer& other) { // if already exist 
        std::cout << "copy assignment\n";
        if (&other == this) 
            return *this;

        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new elem_t[capacity_];
        // std::strcpy(data_, other.data_);
        for (int i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    buffer& operator=(const buffer&& other) noexcept {
        std::cout << "move assignment\n";
        if (&other == this) 
            return *this;

        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        return *this;
    }

    ~buffer() noexcept {
        std::cout << "dtor\n";
        delete[] data_;
    }

public:

    elem_t& at(size_t num) const {
        if (num >= size_)
            std::abort();
        return data_[num];
    } 
    elem_t& operator[](size_t num) {
        if (num >= size_)
            std::abort();
        return data_[num];
    }

    void push_elem(elem_t new_elem) { //without realloc
        if (size_ == capacity_)
            return;
        data_[size_++] = new_elem;
    }
    void pop_elem() {
        if (size_ == 0)
            return;
        size_--;
    }
};
}

#endif // BUFFER