#pragma once

#include "camera/cameraParams.h"
#include "math/vec3.h"
#include "math/matrix.h"
#include <cmath>
#include "utils/math.h"
#include "core/ray.h"


class Camera {
public: 
    
    CameraParams params;

    // Derived
    
    double focal_length_m;
    double lens_radius;
    double vfov;
    matrix camera_to_world;

    virtual ~Camera() = default;
    virtual Ray generateRay(double s, double t) const = 0;
    virtual void setup(double aspect_ratio) = 0;

protected:
    double aspect_ratio;

    void computeDerived(double aspect_ratio) {
        focal_length_m = params.focal_length / 1000.0;
        vfov = 2.0 * radians_to_degrees(std::atan(((params.aperture[1] / 1000) / 2.0) / focal_length_m));
        lens_radius = (params.fstop > 0.0) ? focal_length_m / (2.0 * params.fstop) : 0.0;

        vec3 world_forward = normalize(params.lookat - params.position);
        vec3 world_right = normalize(cross(world_forward, params.getVup()));
        vec3 world_up = normalize(cross(world_right, world_forward));

        //camera_to_world = matrix(world_right, world_up, -world_forward, params.position);
        camera_to_world = matrix(
                vec4(world_right.x, world_up.x, -world_forward.x, 0),
                vec4(world_right.y, world_up.y, -world_forward.y, 0),
                vec4(world_right.z, world_up.z, -world_forward.z, 0),
                vec4(params.position, 1)
                );
    }
};

