#pragma once
#include <vector>
#include <primitives.h>
#include "objLoader.h"

struct SceneData {

    std::vector<Sphere> spheres = {};
    std::vector<Mesh> meshes = {};
    ObjLoader teapotModel {"./assets/models/teapot.obj"};
    Vec3<float> lightDir = { 0.3f, 0.5f, -1.0f } ;
    SceneData() {
         spheres.emplace_back( 1.0f, Vec3{0.0f, -1.0f, 0.0f}, Materials::glass);
                meshes.emplace_back(teapotModel.LoadMesh(Materials::gold));
    }
};

