#pragma once
#include <vector>
#include <primitives.h>

struct SceneData {
    std::vector<Sphere> spheres = {};
    std::vector<Triangle> triangles = {};
    Vec3<float> lightDir = { -0.3f, -0.5f, 1.0f } ;
    int maxReflectionDepth = 5;
    SceneData() {
         lightDir = Vec3<float>{ -0.3f, -0.5f, 1.0f }.normalized();
         triangles = {
            // triangle plane floor
           { Vec3<float>{ -5.0f, -1.0f, -1.0f },
            Vec3<float>{ 5.0f, -1.0f, -1.0f },
            Vec3<float>{ 0.0f, -1.0f, -10.0f }, Materials::plastic },
        };
    }
};

