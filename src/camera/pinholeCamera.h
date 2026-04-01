#pragma once

#include "camera/camera.h"
#include "core/ray.h"
#include <cmath>
#include "utils/math.h"
#include "math/vec3.h"
#include "math/matrix.h"


class PinholeCamera : public Camera {
public:

    Ray generateRay(double s, double t) const override {
        double scale = std::tan(degrees_to_radians(vfov * 0.5));     
        double x = (2.0 * s - 1.0) * scale * aspect_ratio;
        double y = (1.0 - 2.0 * t) * scale;
        
        vec3 cam_direction = normalize(vec3(x, y, -1));

        vec3 world_direction = normalize(rotate(cam_direction, camera_to_world));
        vec3 world_origin = params.position;

        return Ray(world_origin, world_direction, 0.0);
    }

    void setup(double aspect_ratio) override {
        this->aspect_ratio = aspect_ratio;
        computeDerived(aspect_ratio);
    }
};

