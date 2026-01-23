#include <ppm.h>
#include <primitives.h>
#include <scene.h>

int main() {
    PPMFile ppm("./assets/output.ppm", 255, 1000, 1000);
    Camera camera{ ppm.getWidth(), ppm.getHeight() };

    for (int y = 0; y < ppm.getHeight(); ++y) {
        for (int x = 0; x < ppm.getWidth(); ++x) {
            SceneData scene;
            Vec3<float> pixel{
                camera.getNDCx(x),
                -camera.getNDCy(y),
                camera.focalLength
            };
            Ray ray{
                camera.origin,
                (pixel - camera.origin).normalized()
            };
            Color pixelColor = trace(ray, scene,0);
            ppm.writePixel(pixelColor);
        }
    }
}