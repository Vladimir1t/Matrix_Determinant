#ifndef BUFFER
#define BUFFER

#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace my {

template<class elem_t> 
class proxy_buffer {

private:

    elem_t* row_ = nullptr;

public:

    proxy_buffer(elem_t* row) : row_(row) {}

    elem_t& operator[](size_t index) {
        return row_[index];
    }
    const elem_t& operator[](size_t index) const {
        return row_[index];
    }
}; 

template<class elem_t>
class buffer {

private:
    size_t size_        = 0;
    size_t matrix_size_ = 0;
    size_t capacity_    = 0;
    elem_t* data_       = nullptr;
    
public: 
    
    buffer(size_t matrix_size) {

        if (matrix_size <= 0) {
            std::abort(); 
        }
        matrix_size_ = matrix_size;
        capacity_ = matrix_size_ * matrix_size_; 
        data_ = new elem_t[capacity_]; 
    }

    buffer() = default;

    buffer(const buffer& other) noexcept { 
        //std::cout << "copy ctor\n";
        capacity_ = other.capacity_;
        size_ = other.size_;
        matrix_size_ = other.matrix_size_;
        data_ = new elem_t[capacity_];
        for (int i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    buffer(const buffer&& other) noexcept {  
        //std::cout << "move ctor\n";
        data_ = other.data_;
        other.data_ = nullptr;
    }

    buffer& operator=(const buffer& other) { 
        //std::cout << "copy assignment\n";
        if (&other == this) 
            return *this;

        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        matrix_size_ = other.matrix_size_;
        data_ = new elem_t[capacity_];
        for (int i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    buffer& operator=(const buffer&& other) noexcept {
        //std::cout << "move assignment\n";
        if (&other == this) 
            return *this;

        delete[] data_;
        size_ = other.size_;
        matrix_size_ = other.matrix_size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        return *this;
    }

    ~buffer() noexcept {
        //std::cout << "dtor\n";
        delete[] data_;
    }

public:

    elem_t& at(size_t index) const {
        if (index >= size_)
            std::range_error("index out of range");
        return data_[index];
    } 

    proxy_buffer<elem_t> operator[](size_t index) {
        if (index >= size_)
            throw std::range_error("index out of range");
        return proxy_buffer<elem_t>(data_ + index * matrix_size_);
    }

    const proxy_buffer<elem_t> operator[](size_t index) const {
        if (index >= size_)
            throw std::range_error("index out of range");
        return proxy_buffer<elem_t>(data_ + index * matrix_size_);
    }

    void push_elem(elem_t new_elem) { 
        if (size_ == capacity_) {
            void* mem = std::realloc(data_, capacity_ * 2);
            data_ = static_cast<elem_t*>(mem);
            if (!data_)
                throw std::bad_alloc();
            capacity_ *= 2;
        }
        data_[size_++] = new_elem;
    }
    void pop_elem() {
        if (size_ == 0)
            throw std::range_error("buffer is empty");
        size_--;
    }
};
}

#endif // BUFFER