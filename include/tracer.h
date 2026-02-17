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

inline SceneHitInfo traceScene(const Ray& ray, const SceneData& scene);
Color rayTrace(const Ray& ray, const SceneData& scene , int depth ) ;
Color pathTrace(const Ray& ray, const SceneData& scene  ) ;
