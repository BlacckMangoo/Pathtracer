#pragma once
#include <vector>
#include <primitives.h>
#include "modelFileParser.h"

struct SceneData {
    std::vector<Sphere> spheres = {};
    std::vector<Triangle> teapotModelData = {};
    ModelFileParser  teapotModel{"./assets/models/teapot.mdl", teapotModelData}; // loads teapot model from file
    Vec3<float> lightDir = { -0.3f, -0.5f, 1.0f } ;
};

