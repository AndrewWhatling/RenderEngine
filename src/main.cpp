#include "camera/pinholeCamera.h"
#include "math/vec3.h"
#include "shape/sphere.h"
#include "core/ray.h"
#include "math/interval.h"
#include "core/hitRecord.h"
#include <vector>
#include "io/ppm_exporter.h"
#include "shape/triangle.h"


int main() {
    const int width = 400;
    const int height = 300;

    vec3 center(0, 0, 5);
    double radius = 1.0;
    Sphere mySphere(center, radius);
    Triangle myTriangle(vec3(0, 1, 5), vec3(1, 0, 5), vec3(-1, 0, 5));

    PinholeCamera cam;
    cam.params.focal_length = 25;
    cam.setup(1.333);
    
    std::vector<vec3> framebuffer(width * height);
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            double u = (i + 0.5) / width;
            double v = (j + 0.5) / height;
            Ray ray = cam.generateRay(u, v);
            interval t_range(0.001, 1000);
            HitRecord rec;
            
            if (mySphere.intersect(ray, t_range, rec)) {
                vec3 view_normal = transpose_rotate(rec.normal, cam.camera_to_world);
                framebuffer[j*width + i] = (vec3(1) + view_normal) * 0.5;
            } else {
                framebuffer[j*width + i] = vec3(1);
            }
        }
    }
    write_ppm("/home/Andrew/Documents/University/Showreel/RenderEngine/Engine/output/temp.ppm", framebuffer, width, height);
}
