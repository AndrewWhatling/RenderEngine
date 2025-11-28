#pragma once

using namespace std;

// vec2 class
struct vec2 {
    double u, v;
    
    // Define constructors for vec2 class
    vec2() : u(0), v(0) {}
    vec2(double x) : u(x), v(x) {}
    vec2(double x, double y) : u(x), v(y) {}
    
    // Define being able to call u, v components as list values
    double& operator[](int i) {
        switch(i) {
            case 0: return u;
            case 1: return v;
            default: throw std::out_of_range("vec2 index out of range");
        }
    }
    
    // Const version of above
    const double& operator[](int i) const {
        switch(i) {
            case 0: return u;
            case 1: return v;
            default: throw std::out_of_range("vec2 index out of range");
        }
    }

    // Equals operator for vec2 class
    bool operator==(const vec2 &v1) {
        return u == v1.u && v == v1.v;
    }
};


