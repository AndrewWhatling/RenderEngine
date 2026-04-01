#pragma once

struct vec4;

// vec3 class definition
struct vec3 {
    double x, y, z;

    // Definition of default constructors
    vec3();
    vec3(double v);
    vec3(double xx, double yy, double zz);
    explicit vec3(const vec4& v);

    vec3 operator = (const vec3& v);
    
    // Define being able to call x, y, z components as list values
    double& operator[](int i);
    
    // Const version of above
    const double& operator[](int i) const;

    // Negate
    vec3 operator - () const;

    // Math operators vec3 and vec3
    vec3 operator + (const vec3 &v) const;
    vec3 operator += (const vec3 &v);
    vec3 operator - (const vec3 &v) const;
    vec3 operator -= (const vec3 &v);
    vec3 operator * (const vec3 &v) const;
    vec3 operator *= (const vec3 &v);
    vec3 operator / (const vec3 &v) const;
    vec3 operator /= (const vec3 &v);

    // Math operators vec3 and double
    vec3 operator + (const double f) const;
    vec3 operator += (const double f);
    vec3 operator - (const double f) const;
    vec3 operator -= (const double f);
    vec3 operator * (const double f) const;
    vec3 operator *= (const double f);
    vec3 operator / (const double f) const;
    vec3 operator /= (const double f);
    
    // useful functions

    bool near_zero() const;
    static vec3 random();
    static vec3 random(double min, double max);
};

// Alias settings

using point3 = vec3;
using col3 = vec3;

// Vector util functions

vec3 operator + (double f,const vec3 v);
vec3 operator - (double f, const vec3 v);
vec3 operator * (double f, const vec3 v);
vec3 operator / (double f, const vec3 v);

// Cross product
vec3 cross(const vec3 &v1, const vec3 &v2);

// Dot product
double dot(const vec3 &v1, const vec3 &v2);

// Length and Length squared
double length2(const vec3 &v);

double length(const vec3 &v);

// Normalize
vec3 normalize(const vec3 &v);

// Generate random vector
vec3 random_unit_vector();

// Generate random vector based on normal direction
vec3 random_on_hemisphere(const vec3 &normal);

// Generate random vector in x and y, z = 0
vec3 random_in_unit_disk();

// Reflect vector
vec3 reflect(const vec3 v, const vec3 n);

// Refract vector
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);

// Fix degenerate bounding boxes
void fix_bbox_degenerate(vec3& max_bbox, vec3& min_bbox);

// Return exponent
vec3 exp(const vec3 &v);

// Linear interpolation between vectors
vec3 lerp(const vec3& v1, const vec3& v2, double bias);

// Get min and max of two vectors
vec3 min(const vec3& v1, const vec3& v2);
vec3 max(const vec3& v1, const vec3& v2);




