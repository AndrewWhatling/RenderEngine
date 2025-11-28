#pragma once

#include <string>
#include <vector>
#include "pixel.h"

// definition of ppm export
inline void write_ppm(const std::string& filename, int width, int height, const std::vector<std::vector<pixel>>& framebuffer);
