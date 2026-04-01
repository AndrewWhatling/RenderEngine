#pragma once

#include "camera/cameraParams.h"
#include "math/vec3.h"
#include <cmath>
#include "utils/math.h"
#include "core/ray.h"


class Camera {
public: 
    
    CameraParams params;

    // Derived
    
    vec3 facing_dir;
    double focal_length_m;
    double lens_radius;
    double vfov;
    vec3 right;
    vec3 up;

    virtual ~Camera() = default;
    virtual Ray generateRay(double s, double t) const = 0;
    virtual void setup(double aspect_ratio) = 0;

protected:

    void computeDerived(double aspect_ratio) {
        focal_length_m = params.focal_length / 1000.0;
        facing_dir = normalize(params.lookat - params.position);
        vfov = 2.0 * radians_to_degrees(std::atan(((params.aperture[1] / 1000) / 2.0) / focal_length_m));
        lens_radius = (params.fstop > 0.0) ? focal_length_m / (2.0 * params.fstop) : 0.0;
        right = cross(facing_dir, normalize(params.vup));
        up = cross(right, facing_dir);
    }
};

