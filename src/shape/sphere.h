#pragma once

#include "shape/shape.h"
#include "core/ray.h"
#include "math/interval.h"
#include "core/hitRecord.h"
#include <cmath>


class Sphere : public Shape {
public:
    vec3 center;
    double radius;

    Sphere(const vec3& c, const double& r) : center(c), radius(r) {}

    bool intersect(const Ray& ray, const interval& t_range, HitRecord& rec) const override {
        vec3 oc = ray.origin + center;
        double a = length2(ray.direction);
        double b = dot(ray.direction, oc);
        double c = length2(oc) - radius * radius;
        double discriminant = b*b - a*c;

        if (discriminant < 0)
            return false;

        double sqrtd = std::sqrt(discriminant);

        double root = (b - sqrtd) / a;
        if (!t_range.surrounds(root)) {
            root = (b + sqrtd) / a;
            if (!t_range.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.position = ray.at(rec.t);
        vec3 outward_normal = normalize((rec.position - center) / radius);
        rec.set_face_normal(ray, outward_normal);
        
        return true;
    }
 
};

