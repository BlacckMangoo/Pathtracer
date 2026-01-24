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
    for (const Triangle& tri : scene.triangles) {
        if (HitInfo hit; tri.triHit(ray, hit) && hit.t < result.t) {
            result.hit = true;
            result.t = hit.t;
            result.hitPoint = ray.origin + hit.t * ray.direction;
            result.normal = hit.normal;
            result.material = tri.material;
        }
    }
    return result;
}

inline Color trace(const Ray& ray, const SceneData& scene , const int depth) {
    if (depth >= scene.maxReflectionDepth) {return Colors::skyBlue;}
    const SceneHitInfo hit = traceScene(ray,scene);
    if (!hit.hit) {return Colors::skyBlue;}
    const float diffuseIntensity = std::max(0.0f, hit.normal.dot(scene.lightDir));
    constexpr  float ambient = 0.1f;
    const Color directColor = hit.material.baseColor * (ambient + (1.0f - ambient) * diffuseIntensity);
    if (const float reflectivity = hit.material.reflectivity; reflectivity > 0.0f) {
        Vec3<float> reflectDir = ray.direction - 2.0f * ray.direction.dot(hit.normal) * hit.normal;
        reflectDir = reflectDir.normalized();
        const Ray reflectRay{ hit.hitPoint + hit.normal * 0.001f, reflectDir };
        const Color reflectColor = trace(reflectRay, scene, depth + 1);
        // Blend direct color and reflection
        return directColor * (1.0f - reflectivity) + reflectColor * reflectivity;
    }

    return directColor;
}
