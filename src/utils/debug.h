#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <chrono>
#include <functional>
#include <memory>

// Function to calculate time of another function
template<typename Func>
void timeFunction(const std::string& name, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();

    // Execute the function with arguments
    std::invoke(std::forward<Func>(func));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::clog << "[TIMER] \"" << name << "\" took " 
              << duration.count() << " seconds.\n";
}


// basic print statement for C++ debugging
inline void print(const std::string& message) {
    std::cout << message << std::endl;
}

