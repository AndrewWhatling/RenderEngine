#pragma once

#include "../core/color.h"
#include <vector>
#include <string>
#include "pixel.h"

inline void write_exr16(const std::string& filename, int width, int height, const std::vector<std::vector<pixel>>& framebuffer);
