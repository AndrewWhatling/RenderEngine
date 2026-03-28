#pragma once

// vec2 class
struct vec2 {
    double u, v;
    
    // Define constructors for vec2 class
    vec2();
    vec2(double x);
    vec2(double x, double y);
    
    // Define being able to call u, v components as list values
    double& operator[](int i);
    
    // Const version of above
    const double& operator[](int i) const;

    // Comparison operators for vec2 class
    bool operator==(const vec2 &v) const;
    bool operator!=(const vec2 &v) const;
};


