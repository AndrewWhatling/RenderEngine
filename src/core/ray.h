#pragma once

#include "math/vec3.h"

struct Ray {
    vec3 origin, direction;
    double time = 0.0;

    Ray() = default;
    Ray(const vec3& origin, const vec3& direction, double time)
        : origin(origin), direction(direction), time(time) {}

    vec3 at(double t) const {
        return origin + (t * direction);
    }
};

