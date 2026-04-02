#pragma once

#include "core/ray.h"
#include "math/interval.h"
#include "core/hitRecord.h"


class Shape {
public:
    
    virtual ~Shape() = default;

    virtual bool intersect(const Ray& ray, const interval& t_range, HitRecord& rec) const = 0;

};

