#pragma once

#include "math/vec3.h"
#include "math/vec2.h"

struct CameraParams {
    vec3 position = vec3(0.0);
    vec3 lookat = vec3(0.0, 0.0, -1.0);

    vec3 forward = vec3(0.0, 0.0, -1.0);
    vec3 vup = vec3(0.0, 1.0, 0.0);

    double focal_length = 50.0;
    double focal_distance = 5.0;
    vec2 aperture = vec2(25.34, 14.25); 
    double fstop = 2.8;
    
    double shutter_open = 0.0;
    double shutter_closed = 0.0;
};

