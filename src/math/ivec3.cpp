#include "math/ivec3.h"
#include <stdexcept>


// Define constructors for ivec3 class
ivec3::ivec3() : x(0), y(0), z(0) {}
ivec3::ivec3(int v) : x(v), y(v), z(v) {}
ivec3::ivec3(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

// Define being able to call x, y, z components as list values
int& ivec3::operator[](int i) {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("ivec3 index out of range");
    }
}

// Const version of the above
const int& ivec3::operator[](int i) const {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("ivec3 index out of range");
    }
}

// Comparison operators for ivec3
bool ivec3::operator!=(const ivec3 &v) const {
    return !(*this == v);
}

bool ivec3::operator==(const ivec3 &v) const {
    return x == v.x && y == v.y && z == v.z;
}

