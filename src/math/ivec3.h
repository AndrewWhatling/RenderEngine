#pragma once

// Integer vec3 class
struct ivec3 {
    int x, y, z;
    
    // Define constructors for ivec3 class
    ivec3();
    ivec3(int v);
    ivec3(int x_, int y_, int z_);

    // Define being able to call x, y, z components as list values
    int& operator[](int i);

    // Const version of the above
    const int& operator[](int i) const;

    // Comparison operators for ivec3
    bool operator==(const ivec3 &v) const;
    bool operator!=(const ivec3 &v) const;

};

