#pragma once

#include "../core/math/vec3.h"
#include "../core/utils.h"

class camera {
public:
    // Default camera settings
    point3 center = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    point3 vup = point3(0, 1, 0);

    double sensor_width = 25.34; // mm super 35 sensor size, blackmagic mini ursa 4.6K default
    double focal_length = 35.0; // 35mm default focal length
    double f_stop = 2.8;
    
    point3 facing_dir;
    double focus_distance;
    double focal_length_m;
    double lens_radius;
    double defocus_angle;
    double vfov;

    // Calculate additional default values after setting dependencies

    void compute_derived(double aspect_ratio) {
        // Focal length to meters
        focal_length_m = focal_length / 1000;
        // Camera sensor height in meters
        double sensor_height = (sensor_width / 1000) / aspect_ratio;
        // Calculate vertical field of view
        vfov = 2.0 * radians_to_degrees(std::atan((sensor_height / 2.0) / focal_length_m));
        // Calculate defocus angle
        defocus_angle = 2.0 * radians_to_degrees(std::atan(1.0 / (2.0 * f_stop)));
        // Calculate radius of lens
        lens_radius = focal_length_m / (2.0 * f_stop);
        // Calculate the facing direction of the camera
        facing_dir = normalize(center - lookat);
        // Calculate focal distance of camera
        focus_distance = length(center - lookat);
    }
};


