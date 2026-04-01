#pragma once

#include "math/vec3.h"


struct vec4 {
    double x, y, z, w;

    vec4();
    vec4(double v);
    vec4(double xx, double yy, double zz, double ww);
    vec4(vec3 v);
    vec4(vec3 v, double ww);
    
    vec4 operator = (const vec4& v);

    double& operator[](int i);

    const double& operator[](int i) const;

    vec4 operator - () const;
};
