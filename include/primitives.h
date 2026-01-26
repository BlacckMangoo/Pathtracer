#pragma once
#include <ray.h>
#include <material.h>
#include <camera.h>
#include <vector>
#include <bvh.h>

extern int countNoOfTriangleIntersectionChecks;
extern int countNoOfSphereIntersectionChecks;
extern int countNoOfBoxIntersectionChecks;

struct HitInfo {
    float t{};
    float u{}, v{}; // for barycentric coordinates unused for sphere
    Vec3<float> normal;
};


struct Sphere {
    Sphere(const float r, const Vec3<float> &c, const Material &material) : radius(r), center(c), material(material) {
    }

    float radius{};
    Vec3<float> center;
    Material material{};

    bool hit(const Ray &ray, float &t) const;
};


struct Triangle {
    Triangle(const Vec3<float> &vertex0,
             const Vec3<float> &vertex1,
             const Vec3<float> &vertex2)
        : v0(vertex0), v1(vertex1), v2(vertex2) {
    };

    bool triHit(const Ray &ray, HitInfo &hitInfo) const;

private:
    Vec3<float> v0{};
    Vec3<float> v1{};
    Vec3<float> v2{};
};

struct Mesh {
    size_t noOfTriangles{};
    std::vector<Triangle> modelData = {};
    BVHNode bvhNode = {};

     bool hitAABB (const Ray &ray, float tMin, float &tMax) const;
};
