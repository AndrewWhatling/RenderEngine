#pragma once

class interval {
    public:
        // Default values for interval class
        double min, max;
        
        // Define default as infinity/-infinity line
        interval();
        
        interval(double min, double max);
        
        // Return size of interval
        double size() const;
        
        // Check if a value is on interval
        bool contains(double x) const;
        
        // Check if a value is between interval
        bool surrounds(double x) const;
        
        // Clamp value to interval range
        double clamp(double x) const;
        
        // increase interval by padding number
        interval expand(double delta) const;
        
        // Create interval from 2 given intervals
        interval(const interval &a, const interval &b);
        
        static const interval empty, universe;

};


