#ifndef MATRIX
#define MATRIX

#include <iostream>

#include "buffer.hpp" 

namespace Matrix {

template<class elem_t>
class matrix {

private:

    size_t size_ = 0;
    elem_t det_  = 0;

public:
    
    my::buffer<elem_t> buffer;

    matrix(size_t size) {
        if (size <= 0)
            std::abort();
        size_ = size;
        my::buffer<elem_t> new_buffer(size_);
        buffer = new_buffer;
    }

    elem_t calculate_det() {
        const double epsilon_ = 0.0000001;
        double det = 1;

        // for (int i = 0; i < size_; ++i) {
        //     for (int j = 0; j < size_; ++j) {
        //         std::cout << buffer[i][j] << ' ';
        //     }
        //     std::cout << '\n';
        // }

        for (int i = 0; i != size_; ++i) {

            // if (std::fabs(buffer[i][i]) < epsilon_) {
            //     bool swapped = false;
            //     for (int j = i + 1; j < size_; ++j) {
            //         if (std::fabs(buffer[i][j]) > epsilon_) {
            //             std::swap(buffer[i], buffer[j]); // меняем строки 
            //             det *= -1;
            //             swapped = true;
            //         }
            //     }
            //     if (!swapped)
            //         return 0;
            // }
            for (int k = i + 1; k < size_; ++k) {
                elem_t factor = buffer[k][i] / buffer[i][i]; 
                for (int j = i; j < size_; ++j) {
                    buffer[k][j] -= factor * buffer[i][j];
                }
            }
            det *= buffer[i][i];
        }

        return det;

    }

    //elem_t* operator[](size_t row) {
    //    if (row >= size_)
    //        std::abort();
    //    return &buffer[row * size_];
    //}
    const elem_t* operator[](size_t row) const {
        if (row >= size_)
            std::abort();

        return &buffer[row * size_];
    }
};
}

#endif // MATRIX