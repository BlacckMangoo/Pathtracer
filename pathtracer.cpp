#include <pathtracer.h>
#include <cmath>

constexpr float EPSILON = 1e-4f;


inline SceneHitInfo traceScene(const Ray& ray, const SceneData& scene) {
    SceneHitInfo result{};

    for (const Sphere& s : scene.spheres) {
        if (float t= std::numeric_limits<float>::max() ; s.hit(ray, t) && t < result.t) {
            result.hit = true;
            result.t = t;
            result.hitPoint = ray.origin + t * ray.direction;
            result.normal = (result.hitPoint - s.center).normalized();
            result.material = s.material;
        }
    }

    for ( const auto& triangle : scene.teapotModelData ) {
        if (HitInfo hit; triangle.triHit(ray, hit) && hit.t < result.t) {
            result.hit = true;
            result.t = hit.t;
            result.hitPoint = ray.origin + hit.t * ray.direction;
            result.normal = hit.normal.normalized();
            result.material = Materials::gold;
        }
    }

    return result;
}

Color trace(const Ray& ray, const SceneData& scene) {
    const SceneHitInfo hit = traceScene(ray,scene);
    if (!hit.hit) {return Colors::skyBlue;}
    const Vec3<float> n = hit.normal.normalized();
    const Vec3<float> l = scene.lightDir.normalized();
    const float diffuseIntensity = std::max(0.0f, n.dot(l));
    constexpr  float ambient = 0.3f;
    const Color directColor = hit.material.baseColor * (ambient + ((1.0f - ambient) * diffuseIntensity));

    return directColor;
}