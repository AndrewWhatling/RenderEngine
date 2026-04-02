#include "math/interval.h"
#include "utils/constants.h"
#include <cmath>


// Define default as infinity/-infinity line
interval::interval() : min(+infinity), max(-infinity) {} // Default interval is empty

interval::interval(double min, double max) : min(min), max(max) {}

// Create interval from 2 given intervals
interval::interval(const interval &a, const interval &b) {
    min = std::min(a.min, b.min);
    max = std::max(a.max, b.max); 
}

// Return size of interval
double interval::size() const {
    return max - min;
}

// Check if a value is on interval
bool interval::contains(double x) const {
    return min <= x && x <= max;
}

// Check if a value is between interval
bool interval::surrounds(double x) const {
    return min < x && x < max;
}

// Clamp value to interval range
double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// increase interval by padding number
interval interval::expand(double delta) const {
    auto padding = delta/2;
    return interval(min - padding, max + padding);
}

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

