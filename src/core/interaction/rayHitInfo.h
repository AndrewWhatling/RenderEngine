#pragma once

#include <csignal>
#include "../aabb.h"
#include "../math/vec3.h"
#include "../../material/material.h"

//class material;

class rayHitInfo {
public:
    point3 P;
    vec3 N;
    shared_ptr<material> mat;
    double t;
    bool front_face;
    double object_id = -1;
    double mat_id = -1;

    void set_face_normal(const ray &r, const vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0.0;
        N = front_face ? outward_normal : -outward_normal;
    }

    void update_mat() {
        if (mat) mat_id = mat->get_id();
    }
};


class sceneObject {
public:
    double id = -1;

    virtual ~sceneObject() = default;

    virtual bool intersect(const ray &r, interval ray_t, rayHitInfo &ray_hit_info) const = 0;

    virtual aabb bounding_box() const = 0;
};


