#include <ppm.h>
#include <primitives.h>
#include <scene.h>
#include <tracer.h>
#include "profiler.h"
#include <random>
#include <cmath>



constexpr int SAMPLES = 100;
int main() {
    Profiler profiler ;

    PPMFile ppm("./assets/output.ppm", 255, 200, 200);
    Camera camera{ ppm.getWidth(), ppm.getHeight(),3.0f };

    // Create scene ONCE before rendering
    SceneData scene;

    for (int y {}; y < ppm.getHeight(); ++y) {
        for (int x {}; x < ppm.getWidth(); ++x) {
            Vec3 pixel{camera.getNDCx(x),-camera.getNDCy(y),camera.origin.z - camera.focalLength};
            Color pixelColor ;
            for ( int i{} ; i < SAMPLES; ++i) {
                Vec3<float> jitter {
                     (RandomFloat() - 0.5f) / static_cast<float>(ppm.getWidth()),
                     (RandomFloat() - 0.5f) / static_cast<float>(ppm.getHeight()),
                     0.0f
                 };
                 Vec3<float> jitteredPixel = pixel + jitter ;
                 Ray ray{camera.origin,(jitteredPixel - camera.origin).normalized()};
                 pixelColor = pixelColor + pathTrace(ray, scene);
            }
            pixelColor = pixelColor * (1.0f / static_cast<float>(SAMPLES));

            pixelColor = {
                std::min(pixelColor.r, 1.0f) * 255.0f,
                std::min(pixelColor.g, 1.0f) * 255.0f,
                std::min(pixelColor.b, 1.0f) * 255.0f
            };

            ppm.writePixel(pixelColor);
        };
         std::cout << "\rRendering Progress: " << (y + 1) * 100 / ppm.getHeight() << "%" << std::flush;

    }

    return 0;
}
