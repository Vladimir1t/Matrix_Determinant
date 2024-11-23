#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <stdexcept>
#include <cmath>

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
            throw std::invalid_argument("size <= 0");
        size_ = size;
        my::buffer<elem_t> new_buffer(size_);
        buffer = new_buffer;
    }

    /** @brief Gauss method of calculating determinant
     */
    elem_t calculate_det() {
        const double epsilon_ = 0.0000001;
        elem_t det = 1;

        for (int i = 0; i != size_; ++i) {

            if (std::fabs(buffer[i][i]) < epsilon_) {
                bool swapped = false;
                for (int j = i + 1; j < size_; ++j) {
                    if (std::fabs(buffer[i][j]) > epsilon_) {
                        for (int k = 0; k < size_; ++k) {
                            std::swap(buffer[i][k], buffer[j][k]); 
                        }
                        det *= -1;
                        swapped = true;
                    }
                }
                if (!swapped)
                    return 0;
            }
            for (int k = i + 1; k < size_; ++k) {
                elem_t factor = buffer[k][i] / buffer[i][i]; 
                for (int j = i; j < size_; ++j) {
                    buffer[k][j] -= factor * buffer[i][j];
                }
            }
            det *= buffer[i][i];
        }
        det_ = det;

        return det_;
    }
};
}

#endif // MATRIX