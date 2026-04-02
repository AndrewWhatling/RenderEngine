#pragma once

#include <iostream>
#include <fstream>
#include <vector>


void write_ppm(std::string filepath, const std::vector<vec3>& framebuffer, int width, int height) {
    std::ofstream ofs(filepath);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    
    for (const auto& color : framebuffer) {
        int ir = static_cast<int>(255.999 * color.x);
        int ig = static_cast<int>(255.999 * color.y);
        int ib = static_cast<int>(255.999 * color.z);
        ofs << ir << ' ' << ig << ' ' << ib << '\n';
    }
    ofs.close();

    std::cout << "Image written to output.ppm\n";
};


