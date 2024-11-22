#ifndef MATRIX
#define MATRIX

#include <iostream>

#include "buffer.hpp" 

namespace matrix {

template<class elem_t>
class determinant {

private:

    size_t size_ = 0;
    elem_t det_;

public:
    
    my::buffer<elem_t> buffer;

    determinant(size_t size) {
        if (size <= 0)
            std::abort();
        size_ = size;
        my::buffer<elem_t> new_buffer(size_ * size_);
        buffer = new_buffer;
    }

    void calculate_det() {
        const double epsilon_ = 0.0000001;
        double det;

        for (int i = 0; i != size_; ++i) {

            if (buffer[i][i] < epsilon_)
            {}
        }

    }

    elem_t* operator[](size_t row) {
        if (row >= size_)
            std::abort();

        return &buffer[row * size_];
    }
    const elem_t* operator[](size_t row) const {
        if (row >= size_)
            std::abort();

        return &buffer[row * size_];
    }

};

}

#endif // MATRIX