#pragma once

#include "utils/constants.h"


inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double radians_to_degrees(double radians) {
    return radians * (180.0 / pi);
}


