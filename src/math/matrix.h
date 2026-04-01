#pragma once

#include "math/vec4.h"
#include "math/vec3.h"


struct matrix {
    vec4 x, y, z, w;

    matrix();
    matrix(double v);
    matrix(vec4 xx, vec4 yy, vec4 zz, vec4 ww);
    matrix(vec3 xx, vec3 yy, vec3 zz, vec3 ww);
    matrix(vec3 xx, vec3 yy, vec3 zz);
    
    matrix& operator = (const matrix& m);

    vec4& operator[](int i);

    const vec4& operator[](int i) const;

    matrix operator - () const;
};

