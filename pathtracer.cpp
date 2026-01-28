#include <pathtracer.h>
#include <cmath>
#include <stack>

constexpr float EPSILON = 1e-4f;

inline SceneHitInfo traceScene(const Ray& ray, const SceneData& scene) {
    SceneHitInfo result{};
    {
        for (const Sphere& s : scene.spheres) {
            if (float t= std::numeric_limits<float>::max() ; s.hit(ray, t) && t < result.t) {
                result.hit = true;
                result.t = t;
                result.hitPoint = ray.origin + t * ray.direction;
                result.normal = (result.hitPoint - s.center).normalized();
                result.material = s.material;
            }
        }
    }

    for ( const auto&[modelData, bvh]: scene.meshes ) {
        // BVH traversal
         std::stack<int> nodeStack;
         nodeStack.push(bvh.rootIndex);

         while (!nodeStack.empty()) {
             const int nodeIndex = nodeStack.top();
             nodeStack.pop();

             const auto&[box, left, right, startIndex, count, isLeafNode] = bvh.nodes[nodeIndex];

             if (!hitAABB(ray, EPSILON, result.t, box))
                 continue;

             if (isLeafNode) {
                 for (int i = 0; i < count; ++i) {
                     const Triangle& tri = modelData[startIndex + i];
                     if (HitInfo hitInfo;
                         tri.triHit(ray, hitInfo) && hitInfo.t < result.t) {
                         result.hit = true;
                         result.t = hitInfo.t;
                         result.hitPoint = ray.origin + hitInfo.t * ray.direction;
                         result.normal = hitInfo.normal;
                         result.material = Materials::gold; // default material for triangles
                     }
                 }
             } else {
                 nodeStack.push(left);
                 nodeStack.push(right);
             }
         }
    }
    return result;
}

Color trace(const Ray& ray, const SceneData& scene, int depth = 0)
{
    if (depth > 3) return Colors::skyBlue;

    const SceneHitInfo hit = traceScene(ray, scene);
    if (!hit.hit)
        return Colors::skyBlue;

    Vec3<float> n = hit.normal.normalized();
    if (n.dot(ray.direction) > 0.0f)
        n = -n;

    Vec3<float> l = scene.lightDir.normalized();
    const float diffuseIntensity = std::max(0.0f, n.dot(l));

    constexpr float ambient = 0.3f;
    Color directColor =
        hit.material.baseColor *
        (ambient + (1.0f - ambient) * diffuseIntensity);

    const float reflectance = hit.material.reflectance;
    if (reflectance <= 0.0f)
        return directColor;

    const Vec3<float> reflectDir =
        ray.direction - 2.0f * ray.direction.dot(n) * n;

    const Ray reflectRay(
        hit.hitPoint + n * EPSILON,
        reflectDir.normalized()
    );

    const Color reflectedColor = trace(reflectRay, scene, depth + 1);

    return directColor * (1.0f - reflectance)
         + reflectedColor * reflectance;
}
