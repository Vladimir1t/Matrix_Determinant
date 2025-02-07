#ifndef BUFFER
#define BUFFER

#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace my {

template<class elem_t> 
class proxy_buffer final {

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
class buffer final {

private:
    size_t  size_        = 0;
    size_t  matrix_rows_ = 0;
    size_t  matrix_col_  = 0;
    size_t  capacity_    = 0;
    elem_t* data_        = nullptr;
    
public: 
    
    buffer() = default;

    buffer(size_t matrix_rows, size_t matrix_col) {

        if (matrix_rows <= 0 || matrix_col <= 0) 
            throw std::invalid_argument("size <= 0"); 
        
        matrix_rows_ = matrix_rows;
        matrix_col_  = matrix_col;

        capacity_ = matrix_rows * matrix_col; 
        data_ = new elem_t[capacity_]; 
    }

    buffer(buffer&& other) noexcept {  
        // std::cout << "move ctor\n";
        data_        = other.data_;
        other.data_  = nullptr;
        capacity_    = other.capacity_;
        size_        = other.size_;
        matrix_rows_ = other.matrix_rows_;
        matrix_col_  = other.matrix_col_;
    }

    template <typename T>
    T *safe_copy(const T* src, size_t src_size) {
        // std::cout << "safe_copy\n";
        T *dest = new T[src_size];
        try {
            for (size_t idx = 0; idx != src_size; ++idx)
                dest[idx] = src[idx];
        }
        catch (...) {
            delete[] dest;
            throw;
        }
        return dest;
    }

    buffer(const buffer& other) { 
        // std::cout << "copy ctor\n";
        data_ = safe_copy(other.data_, other.capacity_);
        capacity_    = other.capacity_;
        size_        = other.size_;
        matrix_rows_ = other.matrix_rows_;
        matrix_col_  = other.matrix_col_;
    }

    buffer& operator=(const buffer& other) { 
        // std::cout << "copy assignment\n";
        if (&other == this) 
            return *this;
        
        elem_t* tmp_data = safe_copy(other.data_, other.capacity_);
        delete[] data_;
       
        data_        = tmp_data;
        size_        = other.size_;
        capacity_    = other.capacity_;
        matrix_col_  = other.matrix_col_;
        matrix_rows_ = other.matrix_rows_;

        return *this;
    }

    buffer& operator=(buffer&& other) noexcept {
        // std::cout << "move assignment\n";
        if (&other == this) 
            return *this;

        delete[] data_;
        data_        = other.data_;
        other.data_  = nullptr;
        size_        = other.size_;
        matrix_rows_ = other.matrix_rows_;
        matrix_col_  = other.matrix_col_;
        capacity_    = other.capacity_;

        return *this;
    }

    ~buffer() noexcept {
        // std::cout << "dtor\n";
        delete[] data_;
    }

public:

    elem_t& at(size_t index) const {
        if (index >= size_) 
            throw std::range_error("index out of range");
        return data_[index];
    } 

    proxy_buffer<elem_t> operator[](size_t index) {
        if (index >= matrix_rows_)
            throw std::range_error("index out of range");
        return proxy_buffer<elem_t>(data_ + index * matrix_col_);
    }

    const proxy_buffer<elem_t> operator[](size_t index) const {
        if (index >= matrix_rows_)
            throw std::range_error("index out of range");
        return proxy_buffer<elem_t>(data_ + index * matrix_col_);
    }

    void push_elem(elem_t new_elem) { 
        if (size_ == capacity_) {
            void* mem = std::realloc(data_, capacity_ * 2);
            data_ = static_cast<elem_t*>(mem);
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