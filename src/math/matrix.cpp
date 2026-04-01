#include "math/matrix.h"
#include "math/vec4.h"
#include "math/vec3.h"

#include <stdexcept>


matrix::matrix() : x(vec4(1, 0, 0, 0)), y(vec4(0, 1, 0, 0)), z(vec4(0, 0, 1, 0)), w(vec4(0, 0, 0, 1)) {}
matrix::matrix(double v) : x(vec4(v)), y(vec4(v)), z(vec4(v)), w(vec4(v)) {}
matrix::matrix(vec4 xx, vec4 yy, vec4 zz, vec4 ww) : x(xx), y(yy), z(zz), w(ww) {}
matrix::matrix(vec3 xx, vec3 yy, vec3 zz, vec3 ww) : x(vec4(xx)), y(vec4(yy)), z(vec4(zz)), w(vec4(ww, 1)) {}
matrix::matrix(vec3 xx, vec3 yy, vec3 zz) : x(vec4(xx)), y(vec4(yy)), z(vec4(zz)), w(vec4(0, 0, 0, 1)) {}

matrix& matrix::operator = (const matrix& m) {
    x = m.x;
    y = m.y;
    z = m.z;
    w = m.w;
    return *this;
}

vec4& matrix::operator[](int i) {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("matrix index out of range");
    }
}

const vec4& matrix::operator[](int i) const {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("matrix index out of range");
    }
}

matrix matrix::operator - () const {
    return matrix(-x, -y, -z, -w);
}
