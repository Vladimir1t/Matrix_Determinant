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
    size_t rows_ = 0;
    size_t col_  = 0;

protected:
    elem_t det_;
    my::buffer<elem_t> buffer_;

public:

    matrix(size_t rows, size_t col): rows_(rows), col_(col) {}

    virtual void print() = 0;
};

template<class elem_t>
class matrix_sq : public matrix<elem_t> {

private:

    using matrix<elem_t>::buffer_;
    using matrix<elem_t>::det_;
    size_t size_ = 0;

public:
    
    matrix_sq(size_t size) : matrix<elem_t>(size, size) {
        if (size <= 0)
            throw std::invalid_argument("size <= 0");
        size_ = size;
        my::buffer<elem_t> new_buffer(size_);
        buffer_ = new_buffer;
    }

    void push_elem(elem_t new_elem) {
        buffer_.push_elem(new_elem);
    }

    void print() override {
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                std::cout << buffer_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    /** @brief Gauss method of calculating determinant
     */
    elem_t calculate_det() {
        const double epsilon_ = 0.0000001;
        elem_t det = 1;

        for (int i = 0; i != size_; ++i) {

            if (std::fabs(buffer_[i][i]) < epsilon_) {
                bool swapped = false;
                for (int j = i + 1; j < size_; ++j) {
                    if (std::fabs(buffer_[i][j]) > epsilon_) {
                        for (int k = 0; k < size_; ++k) {
                            std::swap(buffer_[k][i], buffer_[k][j]); 
                        }
                        det *= -1;
                        swapped = true;
                    }
                }
                if (!swapped)
                    return 0;
            }
            #ifndef NDEBUG
                std::cout << "swapped collums\n";
                print();
            #endif 

            for (int k = i + 1; k < size_; ++k) {
                elem_t factor = buffer_[k][i] / buffer_[i][i]; 
                for (int j = i; j < size_; ++j) {
                    buffer_[k][j] -= factor * buffer_[i][j];
                }
            }
            det *= buffer_[i][i];
        }
        det_ = det;

        return det_;
    }
};
}

#endif // MATRIX