#define TINYOBJLOADER_IMPLEMENTATION
#include "objLoader.h"
#include <iostream>
#include <algorithm>
ObjLoader::ObjLoader(const std::filesystem::path& objFilePath) {
    loaded = tinyobj::LoadObj(
        &attrib,
        &shapes,
        &materials,
        &warn,
        &err,
        objFilePath.string().c_str()
    );

    if (!warn.empty()) {
        std::cerr << "OBJ warning: " << warn << '\n';
    }
    if (!err.empty()) {
        std::cerr << "OBJ error: " << err << '\n';
    }

    if (!loaded) {
        std::cerr << "Failed to load OBJ file: " << objFilePath << '\n';
    }
}

std::vector<Triangle> ObjLoader::LoadMesh() const {
    std::vector<Triangle> mesh;
    mesh.reserve(80000);
    if (!loaded) {
        return mesh;
    }

    //  Load vertex positions
    std::vector<Vec3<float>> positions;
    positions.reserve(attrib.vertices.size() / 3);

    for (size_t i = 0; i < attrib.vertices.size(); i += 3) {
        positions.emplace_back(
            attrib.vertices[i],
            attrib.vertices[i + 1],
            attrib.vertices[i + 2]
        );
    }

    //  Build triangles from faces
    for (const auto& shape : shapes) {
        size_t indexOffset = 0;

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            int fv = shape.mesh.num_face_vertices[f];

            // if not triangle, skip
            if (fv != 3) {
                indexOffset += fv;
                continue;
            }

            const auto& i0 = shape.mesh.indices[indexOffset + 0];
            const auto& i1 = shape.mesh.indices[indexOffset + 1];
            const auto& i2 = shape.mesh.indices[indexOffset + 2];

            const Vec3<float>& v0 = positions[i0.vertex_index];
            const Vec3<float>& v1 = positions[i1.vertex_index];
            const Vec3<float>& v2 = positions[i2.vertex_index];

            Triangle tri;
            tri.v0 = v0;
            tri.v1 = v1;
            tri.v2 = v2;

            // centroid
            tri.centroid = (v0 + v1 + v2) * (1.0f / 3.0f);

            // AABB
            tri.box.min = {
                std::min({v0.x, v1.x, v2.x}),
                std::min({v0.y, v1.y, v2.y}),
                std::min({v0.z, v1.z, v2.z})
            };

            tri.box.max = {
                std::max({v0.x, v1.x, v2.x}),
                std::max({v0.y, v1.y, v2.y}),
                std::max({v0.z, v1.z, v2.z})
            };

            mesh.emplace_back(tri);

            mesh.emplace_back(tri);
            indexOffset += 3;
        }
    }
    return mesh;

}