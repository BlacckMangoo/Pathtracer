#pragma once
#include <mathUtils.h>

// TO be used for building BVH in future
struct AABB_box {
    Vec3<float> min{};
    Vec3<float> max{};
};

struct BVHNode {
    AABB_box box{};
};

