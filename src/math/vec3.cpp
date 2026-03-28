#include "math/vec3.h"
#include <stdexcept>

#include "core/utils.h"
#include "core/random.h"
#include <cmath>
#include <algorithm>


// Definition of default constructors
vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(double v) : x(v), y(v), z(v) {}
vec3::vec3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

vec3 vec3::operator = (const vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

// Define being able to call x, y, z components as list values
double& vec3::operator[](int i) {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("vec3 index out of range");
    }
}

// Const version of above
const double& vec3::operator[](int i) const {
    switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("vec3 index out of range");
    }
}

// Negate
vec3 vec3::operator - () const {
    return vec3(-x, -y, -z);
}
// Math operators vec3 and vec3
vec3 vec3::operator + (const vec3 &v) const {
    return vec3 (x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator += (const vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3 vec3::operator - (const vec3 &v) const {
    return vec3 (x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator -= (const vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3 vec3::operator * (const vec3 &v) const {
    return vec3 (x * v.x, y * v.y, z * v.z);
}

vec3 vec3::operator *= (const vec3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

vec3 vec3::operator / (const vec3 &v) const {
    return vec3 (x / v.x, y / v.y, z / v.z);
}

vec3 vec3::operator /= (const vec3 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}
// Math operators vec3 and double
vec3 vec3::operator + (const double f) const {
    return vec3 (x + f, y + f, z + f);
}

vec3 vec3::operator += (const double f) {
    x += f;
    y += f;
    z += f;
    return *this;
}

vec3 vec3::operator - (const double f) const {
    return vec3 (x - f, y - f, z - f);
}

vec3 vec3::operator -= (const double f) {
    x -= f;
    y -= f;
    z -= f;
    return *this;
}
vec3 vec3::operator * (const double f) const {
    return vec3 (x * f, y * f, z * f);
}

vec3 vec3::operator *= (const double f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}
vec3 vec3::operator / (const double f) const {
    return vec3 (x / f, y / f, z / f);
}

vec3 vec3::operator /= (const double f) {
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

// useful functions

bool vec3::near_zero() const {
    auto s = EPSILON;
    return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// Vector util functions
vec3 operator + (double f,const vec3 v) {
    return vec3 (v.x + f, v.y + f, v.z + f);
}

vec3 operator - (double f, const vec3 v) {
    return vec3 (v.x - f, v.y - f, v.z - f);

}
vec3 operator * (double f, const vec3 v) {
    return vec3 (v.x * f, v.y * f, v.z * f);
}

vec3 operator / (double f, const vec3 v) {
    return vec3 (v.x / f, v.y / f, v.z / f); 
}

// Cross product
vec3 cross(vec3 &v1, vec3 &v2) {
    return vec3(
            v1.y * v2.z - v1.z * v2.y,
            -(v1.x * v2.z - v1.z * v2.x),
            v1.x * v2.y - v1.y * v2.x 
            );
}

// Dot product
double dot(const vec3 &v1, const vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Length and Length squared
double length2(const vec3 &v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

double length(const vec3 &v) {
    return sqrt(length2(v));
}

// Normalize
vec3 normalize(const vec3 &v) {
    return v / length(v);
}

// Generate random vector
vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = length2(p);
        if (1e-160 < lensq && lensq <= 1) return p / sqrt(lensq);
    }
}

// Generate random vector based on normal direction
vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// Generate random vector in x and y, z = 0
vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (length2(p) < 1)
            return p;
    }
}

// Reflect vector
vec3 reflect(const vec3 v, const vec3 n) {
    return v - 2*dot(v, n) * n;
}

// Refract vector
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - length2(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}

// Fix degenerate bounding boxes
void fix_bbox_degenerate(vec3& max_bbox, vec3& min_bbox) {
    const double EPS = 1e-4;
    if (fabs(max_bbox.x - min_bbox.x) < EPS) { max_bbox.x += EPS; min_bbox.x -= EPS; }
    if (fabs(max_bbox.y - min_bbox.y) < EPS) { max_bbox.y += EPS; min_bbox.y -= EPS; }
    if (fabs(max_bbox.z - min_bbox.z) < EPS) { max_bbox.z += EPS; min_bbox.z -= EPS; }
}

// return exponent
vec3 exp(const vec3 &v) {
    return vec3(std::exp(v.x), std::exp(v.y), std::exp(v.z));
}

// Linear interpolation between vectors
vec3 lerp(const vec3& v0, const vec3& v1, double bias) {
    return vec3(
            (v0.x * bias) + (v1.x * (1-bias)),
            (v0.y * bias) + (v1.y * (1-bias)),
            (v0.z * bias) + (v1.z * (1-bias))
            ); 
}

