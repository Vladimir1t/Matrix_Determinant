#include <iostream>

#include "matrix.hpp"
#include "buffer.hpp"

/** @brief Matrix_determinant - calculate a determinant of matrix 
 *  [in] size of matrix and its elements
 *  [out] determinant
 */
int main() {

    size_t size;
    if (!(std::cin >> size).good()) {
        std::cout << "wrong size value\n";
        return -1;
    }
    matrix::determinant<double> mat_det(size);
    double new_elem;
    for (int i = 0; i != size * size; ++i) {
        std::cin >> new_elem;
        mat_det.buffer.push_elem(new_elem);
    }
    
    return 0;
}