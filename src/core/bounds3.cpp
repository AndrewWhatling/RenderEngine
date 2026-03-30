#include "core/bounds3.h"
#include "utils/constants.h"


Bounds3::Bounds3() : bbmin(-infinity), bbmax(infinity) {}
Bounds3::Bounds3(const vec3& v) : bbmin(v), bbmax(v) {}
Bounds3::Bounds3(const vec3& v1, const vec3& v2) 
    : bbmin(min(v1, v2)), bbmax(max(v1, v2)) {}

vec3 Bounds3::center() const {
    return (bbmin + bbmax) * 0.5;
}

std::vector<vec3> Bounds3::extent() const {
    return { bbmin, bbmax };
}


