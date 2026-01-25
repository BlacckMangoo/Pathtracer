#include <ppm.h>
#include <primitives.h>
#include <scene.h>
#include <pathtracer.h>

#include "profiler.h"

int main() {
    Profiler profiler ;
    PPMFile ppm("./assets/output.ppm", 255, 64, 64);
    Camera camera{ ppm.getWidth(), ppm.getHeight(),3.0f };
    SceneData scene;
    for (int y = 0; y < ppm.getHeight(); ++y) {
        for (int x = 0; x < ppm.getWidth(); ++x) {
            Vec3 pixel{camera.getNDCx(x),-camera.getNDCy(y),camera.origin.z + camera.focalLength};
            Ray ray{camera.origin,(pixel - camera.origin).normalized()};
            Color pixelColor = trace(ray, scene);
            ppm.writePixel(pixelColor);
        }
        std::cout << "progress" << (y + 1) * 100 / ppm.getHeight() << "%\r" << std::flush;
    }
    return 0;
}
