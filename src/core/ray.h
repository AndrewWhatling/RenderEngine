#pragma once

#include "math/vec3.h"

// Definition of ray class
class ray {
public:
    ray() {}

    ray (const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    const point3 &origin() const { return orig; }
    const vec3 &direction() const { return dir; }

    // Calculate vector along dir from origin multiplied by length t
    point3 at(double t) const {
        return orig + dir * t;
    }

private:
    point3 orig;
    vec3 dir;

};

