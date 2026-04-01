#pragma once

#include "camera/camera.h"
#include "core/ray.h"


class PinholeCamera : public Camera {
public:
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    Ray generateRay(double s, double t) const override {
          
    }
};
