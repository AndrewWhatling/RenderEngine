#include "math/vec2.h"
#include <stdexcept>


// Define constructors for vec2 class
vec2::vec2() : u(0), v(0) {}
vec2::vec2(double x) : u(x), v(x) {}
vec2::vec2(double x, double y) : u(x), v(y) {}

// Define being able to call u, v components as list values
double& vec2::operator[](int i) {
    switch(i) {
        case 0: return u;
        case 1: return v;
        default: throw std::out_of_range("vec2 index out of range");
    }
}

// Const version of above
const double& vec2::operator[](int i) const {
    switch(i) {
        case 0: return u;
        case 1: return v;
        default: throw std::out_of_range("vec2 index out of range");
    }
}

// Equals operator for vec2 class
bool vec2::operator==(const vec2 &v) const {
    return u == v.u && v == v.v;
}

bool vec2::operator!=(const vec2 &v) const {
    return !(*this == v);
}

