#include "primitives.h"

// will be read like if( sphere.hit( ray, t ) ) in main
bool Sphere::hit(const Ray& ray, float& t) const {
    const Vec3<float> oc = ray.origin - center;
    const float a = ray.direction.dot(ray.direction);
    const float b = 2.0f * oc.dot(ray.direction);
    const float c = oc.dot(oc) - radius * radius;
    if (auto roots = findRootsOfQuadratic(a, b, c)) {
        auto [t1, t2] = *roots;
        if (t1 > 0 && t2 > 0) {
            t = std::min(t1, t2);
            return true;
        }
        if (t1 > 0) {
            t = t1;
            return true;
        }
        if (t2 > 0) {
            t = t2;
            return true;
        }
    }
    return false;
}

bool Triangle::triHit(const Ray &ray, HitInfo& hitInfo) const {

    constexpr float EPS = 1e-8f;

    const Vec3<float> edge1 = v1 - v0;
    const Vec3<float> edge2 = v2 - v0;
    const Vec3<float> h = ray.direction.cross(edge2);
    const float a = edge1.dot(h); // determinant which comes in denominator in cramer rules expressions

    if (std::abs(a) < EPS)
        return false; // parallel

    const float f = 1.0f / a;
    const Vec3<float> s = ray.origin - v0;

    hitInfo.u = f * s.dot(h);

    const Vec3<float> q = s.cross(edge1);
    hitInfo.v = f * ray.direction.dot(q);
    if (hitInfo.v < 0.0f || hitInfo.u + hitInfo.v> 1.0f)
        return false;

    hitInfo.t = f * edge2.dot(q);
    if (hitInfo.t <= EPS)
        return false;

    if (hitInfo.u < 0.0f || hitInfo.v > 1.0f)
        return false;
    // smooth shading normals
    const float w = 1.0f - hitInfo.u - hitInfo.v;
    hitInfo.normal = (n0 * w + n1 * hitInfo.u + n2 * hitInfo.v).normalized();
    if (hitInfo.normal.dot(ray.direction) > 0.0f)
    hitInfo.normal = -hitInfo.normal;

    return true;
}