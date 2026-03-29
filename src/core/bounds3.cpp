#include "core/bounds3.h"
#include "core/utils.h"


bounds3::bounds3() : bbmin(-infinity), bbmax(infinity) {}
bounds3::bounds3(const vec3& v) : bbmin(v), bbmax(v) {}
bounds3::bounds3(const vec3& v1, const vec3& v2) 
    : bbmin(min(v1, v2)), bbmax(max(v1, v2)) {}

vec3 bounds3::center() const {
    return (bbmin + bbmax) * 0.5;
}

std::vector<vec3> bounds3::extent() const {
    return { bbmin, bbmax };
}


