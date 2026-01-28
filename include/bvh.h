#pragma once
#include <mathUtils.h>
#include <primitives.h>
#include <algorithm>
// TO be used for building BVH in future


enum class SplitAxis {
    X_AXIS = 1,
    Y_AXIS = 2,
    Z_AXIS = 3
};

struct BVHNode {
    AABB_box box{};
    int left = -1; // index of left child in nodes array
    int right = -1; // index of right child in nodes array
    int startIndex{};
    int count{};
    bool isLeafNode{false};
};

struct BVH {
    int rootIndex = -1;
    std::vector<BVHNode> nodes{};
    int maxTrianglesPerLeaf{8};
    int BuildBVH(int startIndex, int end, std::vector<Triangle> &triangles);
};

inline AABB_box findUnionBox(const int startIndex, const int end, const std::vector<Triangle> &triangles) {
    AABB_box unionBox{};

    for (int i = startIndex; i < end; ++i) {
        unionBox.min.x = std::min(unionBox.min.x, triangles[i].box.min.x);
        unionBox.min.y = std::min(unionBox.min.y, triangles[i].box.min.y);
        unionBox.min.z = std::min(unionBox.min.z, triangles[i].box.min.z);
        unionBox.max.x = std::max(unionBox.max.x, triangles[i].box.max.x);
        unionBox.max.y = std::max(unionBox.max.y, triangles[i].box.max.y);
        unionBox.max.z = std::max(unionBox.max.z, triangles[i].box.max.z);
    }
    return unionBox;
}

inline SplitAxis chooseSplitAxis(const AABB_box &box) {
    if (const Vec3<float> extents = box.max - box.min;
        extents.x >= extents.y && extents.x >= extents.z) {
        return SplitAxis::X_AXIS;
    } else if (extents.y >= extents.x && extents.y >= extents.z) {
        return SplitAxis::Y_AXIS;
    } else {
        return SplitAxis::Z_AXIS;
    }
}

inline bool CompareCentroid(const Triangle &a, const Triangle &b, int axis) {
    if (axis == 1) {
        return a.centroid.x < b.centroid.x;
    } else if (axis == 2) {
        return a.centroid.y < b.centroid.y;
    } else {
        return a.centroid.z < b.centroid.z;
    }
}

inline int BVH::BuildBVH(const int startIndex,
                         const int end,
                         std::vector<Triangle>& triangles)
{
    BVHNode node{};

    // 1. Compute AABB FIRST
    AABB_box unionBox = findUnionBox(startIndex, end, triangles);
    node.box = unionBox;

    // 2. Leaf check
    if (end - startIndex <= maxTrianglesPerLeaf) {
        node.startIndex = startIndex;
        node.count = end - startIndex;
        node.isLeafNode = true;

        int nodeIndex = nodes.size();
        nodes.push_back(node);
        return nodeIndex;
    }
    // we choose the axis which has the highest extent , cuz that means triangles are more spread out in that axis
    //so we get better partitioning

    // 3. Choose split axis
    SplitAxis splitAxis = chooseSplitAxis(unionBox);

    // 4. Sort by centroid
    std::sort(triangles.begin() + startIndex,
              triangles.begin() + end,
              [splitAxis](const Triangle& a, const Triangle& b) {
                  return CompareCentroid(
                      a, b, static_cast<int>(splitAxis));
              });

    // 5. Create internal node
    int nodeIndex = nodes.size();
    nodes.push_back(node); // placeholder

    int mid = startIndex + (end - startIndex) / 2;

    // 6. Recurse
    nodes[nodeIndex].left  = BuildBVH(startIndex, mid, triangles);
    nodes[nodeIndex].right = BuildBVH(mid, end, triangles);


    return nodeIndex;
}




inline bool hitAABB(const Ray& ray, float tMin, float tMax, const AABB_box& box) {

    const float xinv = 1.0f / ray.direction.x;
    const float yinv = 1.0f / ray.direction.y;
    const float zinv = 1.0f / ray.direction.z;
    const float tx1 = (box.min.x - ray.origin.x) * xinv;
    const float tx2 = (box.max.x - ray.origin.x) * xinv;
    const float ty1 = (box.min.y - ray.origin.y) * yinv;
    const float ty2 = (box.max.y - ray.origin.y) * yinv;
    const float tz1 = (box.min.z - ray.origin.z) * zinv;
    const float tz2 = (box.max.z - ray.origin.z) * zinv;
    const float tx_enter = std::min(tx1, tx2);
    const float tx_exit = std::max(tx1, tx2);
    const float ty_enter = std::min(ty1, ty2);
    const float ty_exit = std::max(ty1, ty2);
    const float tz_enter = std::min(tz1, tz2);
    const float tz_exit = std::max(tz1, tz2);
    const float t_enter = std::max(tx_enter, std::max(ty_enter, tz_enter));
    const float t_exit = std::min(tx_exit, std::min(ty_exit, tz_exit));

    if (t_exit < t_enter) {
        return false;
    }
    return true;
}
