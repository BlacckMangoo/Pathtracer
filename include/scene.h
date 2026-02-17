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
        meshes.emplace_back(ModelFileParser::createMesh("./assets/models/teapot.mdl"));
        // Ground sphere
        spheres.emplace_back(15.0f, Vec3<float>(0.0f, -15.0f, 3.0f), Materials::diffuseWhite);

        // Emissive sphere light (simple area light)
        Material lightMat;
        lightMat.albedo = {0.0f, 0.0f, 0.0f};
        lightMat.emission = {15.0f, 40.0f, 15.0f};
        lightMat.roughness = 1.0f;
        lightMat.metallic = 0.0f;

        spheres.emplace_back(2.0f, Vec3<float>(0.0f, 8.0f, 0.0f), lightMat);
    }
};
