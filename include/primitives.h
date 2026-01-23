#pragma once
#include <ray.h>
#include <material.h>
#include <camera.h>


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
             const Vec3<float>& vertex2,const Material& mat)
        : material(mat), v0(vertex0), v1(vertex1) , v2(vertex2) {
        n0 = (v1 - v0).cross(v2 - v0).normalized();
        n1 = n0;
        n2 = n0;
    };

    bool triHit(const Ray &ray, HitInfo& hitInfo) const;
    Material material{};

private:
    Vec3<float> n0, n1, n2;
    Vec3<float> v0{};
    Vec3<float> v1{};
    Vec3<float> v2{};
};

