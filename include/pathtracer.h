#pragma once

#include <scene.h>
#include <ray.h>
#include <color.h>

struct SceneHitInfo {
    bool hit = false;
    float t = std::numeric_limits<float>::max();
    Vec3<float> hitPoint;
    Vec3<float> normal;
    Material material;
};


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

    for (const Mesh& mesh : scene.meshes) {
        for (const auto& triangle : mesh.triangles) {
            if (HitInfo hit; triangle.triHit(ray, hit) && hit.t < result.t) {
                result.hit = true;
                result.t = hit.t;
                result.hitPoint = ray.origin + hit.t * ray.direction;
                result.normal = hit.normal;
                result.material = mesh.material;
            }
        }
    }
    return result;
}

inline Color trace(const Ray& ray, const SceneData& scene , const int depth) {
    const SceneHitInfo hit = traceScene(ray,scene);
    if (!hit.hit) {return Colors::skyBlue;}
    const float diffuseIntensity = std::max(0.0f, hit.normal.dot(-scene.lightDir));
    constexpr  float ambient = 0.1f;
    const Color directColor = hit.material.baseColor * (ambient + (1.0f - ambient) * diffuseIntensity);

    return directColor;
}
