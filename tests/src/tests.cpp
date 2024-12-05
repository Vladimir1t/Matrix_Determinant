#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <cstddef>
#include <vector>
#include <cmath>
#include <utility>
#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(TESTS, small_tests) {
    
    std::ifstream test_file;
    std::filesystem::path file_name = "tests/tests.txt";
    test_file.open(file_name);
    if (!test_file.is_open())
        throw std::invalid_argument("wrong file name");

    size_t size;
    double elem;
    double det_ref;
    bool   all_tests_right = true;
    const double epsilon = 0.000001;

    while (!test_file.eof() && (test_file >> size).good()) {

        Matrix::matrix_sq<double> matrx(size);

        for (int i = 0; i != size * size; ++i) {
            if (!(test_file >> elem).good())
                throw std::invalid_argument("wrong value");
            matrx.push_elem(elem);
        }
        test_file >> det_ref;
        EXPECT_EQ(std::fabs(det_ref - matrx.calculate_det()) < epsilon, true);
    }
}

TEST(TESTS, test_interface) {

    const double epsilon_ = 0.000001;

    // Test 1. Sum
    Matrix::matrix<double> matrx_1(2, 3);
    std::vector<double> elems_1 = {2.1, 3, 4, 1, 0, 3.5}; 
    for (auto elem: elems_1) 
        matrx_1.push_elem(elem);
    
    Matrix::matrix<double> matrx_2 = matrx_1 + matrx_1;
    std::vector<double> mtrx_2_elems = matrx_2.get_elements();
   
    EXPECT_EQ(std::fabs(mtrx_2_elems[0] - 4.2) < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_2_elems[1] - 6)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_2_elems[2] - 8)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_2_elems[3] - 2)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_2_elems[4])       < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_2_elems[5] - 7)   < epsilon_, true);

    // Test 2. Copy ctor
    Matrix::matrix<double> matrx_3(2, 3);
    std::vector<double> elems_3 = {2.1, 3, 4, 1, 8, -1}; 
    for (auto elem: elems_3) 
        matrx_3.push_elem(elem);
    
    Matrix::matrix<double> matrx_4 = matrx_3;
    std::vector<double> mtrx_4_elems = matrx_4.get_elements();
   
    EXPECT_EQ(std::fabs(mtrx_4_elems[0] - 2.1) < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_4_elems[1] - 3)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_4_elems[2] - 4)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_4_elems[3] - 1)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_4_elems[4] - 8)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_4_elems[5] + 1)   < epsilon_, true);

    // Test 3. move ctor
    Matrix::matrix<double> matrx_5(2, 3);
    std::vector<double> elems_5 = {2.1, 3, 4, 1, 0, 3.5}; 
    for (auto elem: elems_5) 
        matrx_5.push_elem(elem);
    
    Matrix::matrix<double> matrx_6(std::move(matrx_5));
    std::vector<double> mtrx_6_elems = matrx_6.get_elements();
   
    EXPECT_EQ(std::fabs(mtrx_6_elems[0] - 2.1) < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_6_elems[1] - 3)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_6_elems[2] - 4)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_6_elems[3] - 1)   < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_6_elems[4])       < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_6_elems[5] - 3.5) < epsilon_, true);

    // Test 4. move assignment
    Matrix::matrix<double> matrx_7(2, 3);
    std::vector<double> elems_7 = {2.15, 3, -1, 1, 0, 3.5}; 
    for (auto elem: elems_7) 
        matrx_7.push_elem(elem);
    
    Matrix::matrix<double> matrx_8(2, 2);
    matrx_8 = std::move(matrx_7);
    std::vector<double> mtrx_8_elems = matrx_8.get_elements();
   
    EXPECT_EQ(std::fabs(mtrx_8_elems[0] - 2.15) < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_8_elems[1] - 3)    < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_8_elems[2] + 1)    < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_8_elems[3] - 1)    < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_8_elems[4])        < epsilon_, true);
    EXPECT_EQ(std::fabs(mtrx_8_elems[5] - 3.5)  < epsilon_, true);

    // какие сделать тесты
    // запрос элемента по индексу больше size
    // не кидает исключения копипрование 
    // провекра консистентного состояния после исключения 
}

TEST(TESTS, exception_tests) {
    Matrix::matrix<double> matrx_9(2, 3);
    Matrix::matrix<double> matrx_10(1, 3);
    EXPECT_THROW(matrx_9 + matrx_10, std::invalid_argument);
   
    my::buffer<int> buf(2, 2);
   
    EXPECT_THROW(buf.at(1),  std::exception);
    EXPECT_THROW(buf.at(10), std::range_error);
}