#define TINYOBJLOADER_IMPLEMENTATION
#include "objLoader.h"
#include <iostream>

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
}

Mesh ObjLoader::LoadMesh(const Material& material) const {
    Mesh mesh;
    mesh.material = material;

    if (!loaded) {
        return mesh;
    }

    // 1. Load vertex positions
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

            // Only triangles supported
            if (fv != 3) {
                indexOffset += fv;
                continue;
            }

            const auto& i0 = shape.mesh.indices[indexOffset + 0];
            const auto& i1 = shape.mesh.indices[indexOffset + 1];
            const auto& i2 = shape.mesh.indices[indexOffset + 2];

            Triangle tri {
                positions[i0.vertex_index],
                positions[i1.vertex_index],
                positions[i2.vertex_index]
            };

            mesh.triangles.push_back(tri);

            indexOffset += 3;
        }
    }

    return mesh;
}
