#pragma once

#include "shape/shape.h"
#include "math/vec3.h"
#include "core/ray.h"
#include "core/hitRecord.h"
#include "utils/constants.h"
#include <cmath>


class Triangle : public Shape {
public:    
    vec3 v0, v1, v2;
    
    Triangle(const vec3& a, const vec3& b, const vec3& c) : v0(a), v1(b), v2(c) {}
    
    bool intersect(const Ray& ray, const interval& t_range, HitRecord& rec) const override {
        vec3 edge1 = v1 - v0;
        vec3 edge2 = v2 - v0;
        vec3 h = cross(ray.direction, edge2);
        double a = dot(edge1, h);

        if (std::abs(a) < EPSILON)
            return false;

        double f = 1.0 / a;
        vec3 s = ray.origin - v0;

        double u = f * dot(s, h);
        if (u < 0.0 || u > 1.0) 
            return false;

        vec3 q = cross(s, edge1);
        double v = f * dot(ray.direction, q);
        if (v < 0.0 || u + v > 1.0)
            return false;

        double t = f * dot(edge2, q);
        if (!t_range.contains(t))
            return false;

        rec.t = t;
        rec.position = ray.at(t);
        // This is only flat shading, use as fallback if no normals are on mesh
        // Calculate smooth shading later
        vec3 normal = normalize(cross(edge1, edge2));
        rec.set_face_normal(ray, normal);
        
        return true;
    }
};

