#include "math/vec3.h"


struct BSDFSample {
    vec3 wi;
    vec3 f;
    float pdf;
    bool specular;
};

class BSDF {
public:
    virtual vec3 f(const vec3& wo, const vec3& wi) const = 0;
    virtual BSDFSample sample(const vec3& wo) const = 0;
    virtual float pdf(const vec3& wo, const vec3& wi) const = 0;
};

