#pragma once

#include "math/vec3.h"
#include <vector>

struct bounds3 {
    vec3 bbmin;
    vec3 bbmax;

    bounds3();
    bounds3(const vec3& v);
    bounds3(const vec3& v1, const vec3& v2);

    vec3 center() const;
    std::vector<vec3> extent() const;
};

