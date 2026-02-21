#include <tracer.h>
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

Color rayTrace(const Ray& ray, const SceneData& scene, const int depth = 0)
{
    if (depth > 3) return Colors::skyBlue;

    const auto& hit = traceScene(ray, scene);
    if (!hit.hit)
        return Colors::skyBlue;

    Vec3<float> n = hit.normal.normalized();
    if (n.dot(ray.direction) > 0.0f)
        n = -n;

    Vec3<float> l = scene.lightDir.normalized();
    const float diffuseIntensity = std::max(0.0f, n.dot(l));

    constexpr float ambient = 0.3f;

    const Color directColor =
        hit.material.albedo * (diffuseIntensity + ambient) +
        hit.material.emission;
    const float reflectance  = (1.0f - hit.material.metallic) * hit.material.roughness;
    if (reflectance <= 0.0f)
        return directColor;

    const Vec3<float> reflectDir =
        ray.direction - 2.0f * ray.direction.dot(n) * n;

    const Ray reflectRay(
        hit.hitPoint + n * EPSILON,
        reflectDir.normalized()
    );

    const Color reflectedColor = rayTrace(reflectRay, scene, depth + 1);
    return directColor * (1.0f - reflectance)+ reflectedColor * reflectance;
}


//  samples uniformly distributed over the hemisphere oriented around the normal
Vec3<float> CosineWeightedHemisphere(const Vec3<float>& normal)
{
    const float r1 = RandomFloat();
    const float r2 = RandomFloat();

    const float phi = 2.0f * static_cast<float>(M_PI) * r1;
    const float r   = std::sqrt(r2);
    const float x = r * std::cos(phi);
    const float y = r * std::sin(phi);
    const float z = std::sqrt(1.0f - r2);

    Vec3<float> T;
    if (fabs(normal.x) > 0.1f)
        T = Vec3<float>(0,1,0).cross(normal).normalized();
    else
        T = Vec3<float>(1,0,0).cross(normal).normalized();

    const Vec3<float> B = normal.cross(T);

    // a local new basis -> T, B, normal

    return (T*x + B*y + normal*z).normalized();
}

Color pathTrace(const Ray& ray, const SceneData& scene)
{
    constexpr int MAX_DEPTH = 8;

    Color L{0.0f, 0.0f, 0.0f};
    Color throughput{1.0f, 1.0f, 1.0f};  // Path throughput (βt)

    Ray wo = ray;

    for (int bounce = 0; bounce < MAX_DEPTH; ++bounce)
    {
        auto [hit, t, x, n, mat] = traceScene(wo, scene);

        if (!hit) {
            const Color Le = Colors::skyBlue * 0.5f;
            L = L + throughput * Le;
            break;
        }

        Vec3<float> normal = n.normalized();
        if (normal.dot(wo.direction) > 0.0f)
            normal = -normal;

        if (mat.isEmissive()) {
            L = L + throughput * mat.emission;
            break;
        }

        // returns a random direction sampled from a cosine-weighted hemisphere oriented around the normal in the TBN space of the hit point

        Vec3<float> wi = CosineWeightedHemisphere(normal);

        float pdf = std::max(0.0f, normal.dot(wi)) / static_cast<float>(M_PI);

        if (pdf > 0.0f) {
            throughput = throughput * mat.albedo;
        } else {
            break;
        }
        wo = Ray(x + normal * EPSILON, wi);
    }

    return L;
}




