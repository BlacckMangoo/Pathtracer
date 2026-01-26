#include "modelFileParser.h"


ModelFileParser::ModelFileParser(const std::filesystem::path &modelFilePath, Mesh &mesh) {
    ifStream = std::ifstream(modelFilePath,std::ios::in);
    if (!ifStream.is_open()) {
        throw std::runtime_error("Failed to open model file: " + modelFilePath.string());
    }
    ConstructMeshFromFile( mesh);
}

void ModelFileParser::ConstructMeshFromFile(Mesh &mesh) {
    // construct bounding volume
    float minx = std::numeric_limits<float>::max();
    float miny = std::numeric_limits<float>::max();
    float minz = std::numeric_limits<float>::max();
    float maxx = std::numeric_limits<float>::lowest();
    float maxy = std::numeric_limits<float>::lowest();
    float maxz = std::numeric_limits<float>::lowest();


    // read number of vertices

    ifStream >> m_noOfTriangles;
    // read triangles
    for (size_t i = 0; i < m_noOfTriangles; ++i) {
        float x1, y1, z1;
        ifStream >> x1 >> y1 >> z1;

        minx = std::min(x1, minx);
        miny = std::min(y1, miny);
        minz = std::min(z1, minz);
        maxx = std::max(x1, maxx);
        maxy = std::max(y1, maxy);
        maxz = std::max(z1, maxz);

        float x2, y2, z2;
        ifStream >> x2 >> y2 >> z2;

        minx = std::min(x1, minx);
        miny = std::min(y1, miny);
        minz = std::min(z1, minz);
        maxx = std::max(x1, maxx);
        maxy = std::max(y1, maxy);
        maxz = std::max(z1, maxz);

        float x3, y3, z3;
        ifStream >> x3 >> y3 >> z3;

        minx = std::min(x1, minx);
        miny = std::min(y1, miny);
        minz = std::min(z1, minz);
        maxx = std::max(x1, maxx);
        maxy = std::max(y1, maxy);
        maxz = std::max(z1, maxz);

        // skip blank line
        ifStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        mesh.modelData.emplace_back(
            Vec3<float>(x1, y1, z1),
            Vec3<float>(x2, y2, z2),
            Vec3<float>(x3, y3, z3)
        );
        mesh.noOfTriangles = m_noOfTriangles;
        mesh.bvhNode.box = {
            Vec3<float>(minx, miny, minz),
            Vec3<float>(maxx, maxy, maxz)
        };
    }
}
