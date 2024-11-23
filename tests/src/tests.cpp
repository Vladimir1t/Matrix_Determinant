#include <iostream>
#include <fstream>
#include <cmath>
#include <cstddef>

#include "matrix.hpp"
#include "buffer.hpp"

static int run_tests();

int main() {

    return run_tests();
}

int run_tests() {
    
    std::ifstream test_file;
    test_file.open("tests/tests.txt");
    if (!test_file.is_open())
        return -1;

    size_t size;
    double elem;
    double det_ref;
    bool   all_tests_right = true;
    size_t test_counter = 0;
    const double epsilon = 0.000001;

    while (!test_file.eof() && (test_file >> size).good()) {

        Matrix::matrix<double> mat_det(size);

        for (int i = 0; i != size * size; ++i) {
            if (!(test_file >> elem).good())
                return -1;
            mat_det.buffer.push_elem(elem);
        }
        test_file >> det_ref;
        if (!(std::fabs(det_ref - mat_det.calculate_det()) < epsilon)) {
            std::cout << "test [" << test_counter << "] is incorrect\n";
            all_tests_right = false;
        }
        test_counter++;
    }
    if (all_tests_right) {
        std::cout << "all tests passed\n";
        return 0;
    }
    else 
        return -1;
}