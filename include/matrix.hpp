#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>

#include "buffer.hpp" 

namespace Matrix {

template<class elem_t>
class matrix {

protected:

    size_t rows_ = 0;
    size_t col_  = 0;
    elem_t det_;
    my::buffer<elem_t> buffer_;

public:

    matrix(size_t rows, size_t col): rows_(rows), col_(col) {
        my::buffer<elem_t> new_buffer(rows_, col_);
        buffer_ = new_buffer;
    }

    matrix operator+(const matrix& other) {
        if (rows_ != other.rows_ || col_ != other.col_) {
            throw std::invalid_argument("incorrect sum");
        }

        matrix<elem_t> matrix_sum(rows_, col_);
    
        for (int i = 0; i != rows_; ++i) {
            for (int j = 0; j != col_; ++j) {
                matrix_sum.buffer_[i][j] = buffer_[i][j] + other.buffer_[i][j];  
            }
        }
        return matrix_sum;
    } 

    virtual void print() {

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < col_; ++j) {
                std::cout << buffer_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
    void push_elem(elem_t new_elem) {
        buffer_.push_elem(new_elem);
    }

    std::vector<double> get_elements() {
        std::vector<elem_t> elements(rows_ * col_, 1);
        int indx = 0;
        for (elem_t& elem: elements) 
            elem = buffer_.at(indx++);
        
        return elements;
    }
};

template<class elem_t>
class matrix_sq : public matrix<elem_t> {

private:

    using matrix<elem_t>::buffer_;
    using matrix<elem_t>::det_;
    using matrix<elem_t>::rows_;
    using matrix<elem_t>::col_;
    size_t size_ =  0;

public:
    
    matrix_sq(size_t size) : matrix<elem_t>(size, size) {
        if (size <= 0)
            throw std::invalid_argument("size <= 0");
        size_ = rows_ = col_ = size;
        my::buffer<elem_t> new_buffer(rows_, col_);
        buffer_ = new_buffer;
    }

    // void push_elem(elem_t new_elem) {
    //     buffer_.push_elem(new_elem);
    // }

    void print() override {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < col_; ++j) {
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
        matrix_sq<elem_t> matrix_det = *this;

        for (int i = 0; i != size_; ++i) {

            if (std::fabs(matrix_det.buffer_[i][i]) < epsilon_) {
                bool swapped = false;
                for (int j = i + 1; j < size_; ++j) {
                    if (std::fabs(matrix_det.buffer_[i][j]) > epsilon_) {
                        for (int k = 0; k < size_; ++k) {
                            std::swap(matrix_det.buffer_[k][i], matrix_det.buffer_[k][j]); 
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
                elem_t factor = matrix_det.buffer_[k][i] / matrix_det.buffer_[i][i]; 
                for (int j = i; j < size_; ++j) {
                    matrix_det.buffer_[k][j] -= factor * matrix_det.buffer_[i][j];
                }
            }
            det *= matrix_det.buffer_[i][i];
        }
        det_ = det;

        return det_;
    }
};
}

#endif // MATRIX