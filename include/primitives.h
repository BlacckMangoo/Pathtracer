#pragma once
#include <ray.h>
#include <material.h>
#include <camera.h>
#include <vector>


struct HitInfo {
    float t{} ;
    float u{}, v{}; // for barycentric coordinates unused for sphere
    Vec3<float> normal;

};



struct Sphere {
    Sphere(const float r, const Vec3<float>& c ,const Material& material) : radius(r), center(c) ,material(material) {}
    float radius{};
    Vec3<float> center;
    Material material{};
    bool hit(const Ray &ray, float &t) const;
};




struct Triangle {
    Triangle (const Vec3<float>& vertex0,
             const Vec3<float>& vertex1,
             const Vec3<float>& vertex2)
        :  v0(vertex0), v1(vertex1) , v2(vertex2) {
    };

    bool triHit(const Ray &ray, HitInfo& hitInfo) const;

private:
    Vec3<float> v0{};
    Vec3<float> v1{};
    Vec3<float> v2{};
};


struct Mesh {
    Mesh() = default;
    Mesh( std::vector<Vec3<float>> vertices, const Material& material )
        : material(material) {
        for (size_t i = 0; i + 2 < vertices.size(); i += 3) {
            triangles.emplace_back(vertices[i], vertices[i + 1], vertices[i + 2]);
        }
    }
    std::vector<Triangle> triangles{};
    Material material{};
};