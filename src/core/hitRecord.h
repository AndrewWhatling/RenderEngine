#pragma once

#include "core/ray.h"


struct HitRecord {
    vec3 position;
    vec3 normal;
    double t = 0.0;
    bool front_face = true;

    void set_face_normal(const Ray& ray, const vec3& outward_normal) {
        front_face = dot(ray.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

