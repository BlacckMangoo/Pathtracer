#pragma once
#include <vector>
#include <primitives.h>
#include "modelFileParser.h"
#include <bvh.h>



struct SceneData {
    std::vector<Sphere> spheres = {};
    std::vector<Mesh> meshes = {};
    Vec3<float> lightDir = {-0.3f, -0.5f, 1.0f};

    SceneData() {
        meshes.reserve(3);
        ModelFileParser parser("./assets/models/teapot.mdl", meshes.emplace_back());
    }
};
