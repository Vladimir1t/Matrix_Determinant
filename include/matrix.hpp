#ifndef MATRIX
#define MATRIX

#include <iostream>

#include "buffer.hpp" 

namespace matrix {

template<class T>
class determinant {

private:

    size_t n = 0;

public:
    
    my::buffer<T> buffer;

    determinant(size_t size) {
        my::buffer<T> new_buffer(size * size);
        buffer = new_buffer;
    }

    // T& operator[][](size_t num) {

    // }



};

}

#endif // MATRIX