#include "primitives.h"

int countNoOfTriangleIntersectionChecks = 0;
int countNoOfSphereIntersectionChecks = 0;
int countNoOfBoxIntersectionChecks = 0;

// will be read like if( sphere.hit( ray, t ) ) in main
bool Sphere::hit(const Ray& ray, float& t) const {
    countNoOfSphereIntersectionChecks++;
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

bool Triangle::triHit(const Ray& ray, HitInfo& hitInfo) const {
    countNoOfTriangleIntersectionChecks++;

    constexpr float EPS = 1e-4f;

    const Vec3<float> edge1 = v1 - v0;
    Vec3<float> edge2 = v2 - v0;

    Vec3<float> pvec = ray.direction.cross(edge2);
    float det = edge1.dot(pvec);

    // Ray parallel to triangle
    if (std::abs(det) < EPS)
        return false;

    float invDet = 1.0f / det;

    Vec3<float> tvec = ray.origin - v0;
    float u = tvec.dot(pvec) * invDet;
    if (u < 0.0f || u > 1.0f)
        return false;

    Vec3<float> qvec = tvec.cross(edge1);
    float v = ray.direction.dot(qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f)
        return false;

    float t = edge2.dot(qvec) * invDet;
    if (t <= EPS)
        return false;

    // Write hit info only after success
    hitInfo.t = t;
    hitInfo.u = u;
    hitInfo.v = v;

    hitInfo.normal = edge1.cross(edge2).normalized();

    if ( hitInfo.normal.dot(ray.direction) > 0 ) {
        hitInfo.normal = -hitInfo.normal; // ensure normal faces against ray
    }

    return true;
}

bool Mesh::hitAABB ( const Ray& ray , float tMin , float& tMax  ) const {
    countNoOfBoxIntersectionChecks++;
    float tx1 = (bvhNode.box.min.x - ray.origin.x) * (1/ray.direction.x);
    float tx2 = (bvhNode.box.max.x - ray.origin.x) * (1/ray.direction.x);

    tMin = std::min(tx1, tx2);
    tMax = std::max(tx1, tx2);

    float ty1 = (bvhNode.box.min.y - ray.origin.y) * (1/ray.direction.y);
    float ty2 = (bvhNode.box.max.y - ray.origin.y) *  (1/ray.direction.y);

    tMin = std::max(tMin, std::min(ty1, ty2));
    tMax = std::min(tMax, std::max(ty1, ty2));

    float tz1 = (bvhNode.box.min.z - ray.origin.z) * (1/ray.direction.z);
    float tz2 = (bvhNode.box.max.z - ray.origin.z) * ( 1/ray.direction.z);

    tMin = std::max(tMin, std::min(tz1, tz2));
    tMax = std::min(tMax, std::max(tz1, tz2));

    return tMax >= std::max(tMin, 0.0f);
}
