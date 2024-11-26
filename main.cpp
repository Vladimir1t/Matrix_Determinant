#include <iostream>
#include <cstddef>

#include "matrix.hpp"
#include "buffer.hpp"

/** @brief Matrix_determinant - calculate a determinant of matrix 
 *  [in] size of matrix and its elements
 *  [out] determinant
 */
int main() {
    try {
        size_t size;
        if (!(std::cin >> size).good()) {
            std::cout << "wrong size value\n";
            return -1;
        }
        Matrix::matrix<double> mat_det(size);
        double new_elem;
        for (int i = 0; i != size * size; ++i) {
            if (!(std::cin >> new_elem).good()) {
                std::cout << "wrong elem value\n";
                return -1;
            }
            mat_det.buffer.push_elem(new_elem);
        }
        #ifndef NDEBUG
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << mat_det.buffer[i][j] << ' ';
                }
                std::cout << '\n';
            }
        #endif
        std::cout << mat_det.calculate_det() << '\n';
    }
    catch (const std::exception&) {
        std::cout << "Error\n";
        return -1;
    }
    
    return 0;
}