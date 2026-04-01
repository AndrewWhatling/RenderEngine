#include "math/vec4.h"
#include "math/vec3.h"

#include <stdexcept>


vec4::vec4() : x(0), y(0), z(0), w(0) {}
vec4::vec4(double v) : x(v), y(v), z(v), w(v) {}
vec4::vec4(double xx, double yy, double zz, double ww) : x(xx), y(yy), z(zz), w(ww) {}
vec4::vec4(vec3 v) : x(v.x), y(v.y), z(v.z), w(0) {}
vec4::vec4(vec3 v, double ww) : x(v.x), y(v.y), z(v.z), w(ww) {}

vec4 vec4::operator = (const vec4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

double& vec4::operator[](int i) {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("vec4 index out of range");
    }
}

const double& vec4::operator[](int i) const {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("vec4 index out of range");
    }
}

vec4 vec4::operator - () const {
    return vec4(-x, -y, -z, -w);
}
