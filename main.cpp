#include <ppm.h>
#include <primitives.h>
#include <scene.h>
#include <pathtracer.h>
#include "profiler.h"
#include <random>


float RandomFloat() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

constexpr int Samples = 10 ;
int main() {
    Profiler profiler ;

    PPMFile ppm("./assets/output.ppm", 255, 1000, 1000);
    Camera camera{ ppm.getWidth(), ppm.getHeight(),3.0f };
    SceneData scene;

     for (int y = 0; y < ppm.getHeight(); ++y) {
        for (int x = 0; x < ppm.getWidth(); ++x) {
            Vec3 pixel{camera.getNDCx(x),-camera.getNDCy(y),camera.origin.z - camera.focalLength};
            Color pixelColor ;
            for ( int i{} ; i < Samples; ++i) {
                 Vec3<float> jitter {
                     (RandomFloat() - 0.5f) / static_cast<float>(ppm.getWidth()),
                     (RandomFloat() - 0.5f) / static_cast<float>(ppm.getHeight()),
                     0.0f
                 };
                 Vec3<float> jitteredPixel = pixel + jitter ;
                 Ray ray{camera.origin,(jitteredPixel - camera.origin).normalized()};
                 pixelColor = pixelColor + trace(ray, scene,0);
            }
            pixelColor = pixelColor * (1.0f / static_cast<float>(Samples));
            ppm.writePixel(pixelColor);
        };
         std::cout << "\rRendering Progress: " << (y + 1) * 100 / ppm.getHeight() << "%" << std::flush;
    }

    return 0;
}
