#include <ppm.h>
#include <primitives.h>
#include <scene.h>
#include <pathtracer.h>

#include "profiler.h"

int main() {
    Profiler profiler ;
    PPMFile ppm("./assets/output.ppm", 255, 300, 300);
    Camera camera{ ppm.getWidth(), ppm.getHeight() };
    SceneData scene;
    for (int y = 0; y < ppm.getHeight(); ++y) {
        for (int x = 0; x < ppm.getWidth(); ++x) {
            Vec3 pixel{camera.getNDCx(x),-camera.getNDCy(y),camera.focalLength};
            Ray ray{camera.origin,(pixel - camera.origin).normalized()};
            Color pixelColor = trace(ray, scene,0);
            ppm.writePixel(pixelColor);
        }
    }
    std::cout << scene.spheres.size() << " spheres rendered." << std::endl;
    return 0;
}
