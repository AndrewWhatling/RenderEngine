cmake_minimum_required(VERSION 3.15)
project(Raytracer LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(OpenEXR REQUIRED)

add_executable(Raytracer
    src/main.cpp
    src/math/vec3.cpp
    src/math/ivec3.cpp
    src/math/vec2.cpp
    src/math/interval.cpp
    src/math/vec4.cpp
    src/math/matrix.cpp
    src/core/bounds3.cpp
)

target_link_libraries(Raytracer PRIVATE OpenEXR::OpenEXR)

target_include_directories(Raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

