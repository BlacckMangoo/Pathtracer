#include "modelFileParser.h"




Mesh ModelFileParser::createMesh( const std::filesystem::path& modelFilePath ) {
    Mesh mesh;
    std::ifstream ifStream;
    size_t m_noOfTriangles {};

    ifStream = std::ifstream(modelFilePath,std::ios::in);
    if (!ifStream.is_open()) {
        throw std::runtime_error("Failed to open model file: " + modelFilePath.string());
    }
    ifStream >> m_noOfTriangles;
    mesh.modelData.reserve(m_noOfTriangles);

    // read triangles
    for (size_t i = 0; i < m_noOfTriangles; ++i) {

        float minx = std::numeric_limits<float>::max();
        float miny = std::numeric_limits<float>::max();
        float minz = std::numeric_limits<float>::max();
        float maxx = std::numeric_limits<float>::lowest();
        float maxy = std::numeric_limits<float>::lowest();
        float maxz = std::numeric_limits<float>::lowest();

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

        minx = std::min(x2, minx);
        miny = std::min(y2, miny);
        minz = std::min(z2, minz);
        maxx = std::max(x2, maxx);
        maxy = std::max(y2, maxy);
        maxz = std::max(z2, maxz);

        float x3, y3, z3;
        ifStream >> x3 >> y3 >> z3;

        minx = std::min(x3, minx);
        miny = std::min(y3, miny);
        minz = std::min(z3, minz);
        maxx = std::max(x3, maxx);
        maxy = std::max(y3, maxy);
        maxz = std::max(z3, maxz);

        Triangle tri = {
            Vec3<float>(x1, y1, z1),
            Vec3<float>(x2, y2, z2),
            Vec3<float>(x3, y3, z3)
        };

        tri.centroid = {
            (x1 + x2 + x3) / 3.0f,
            (y1 + y2 + y3) / 3.0f,
            (z1 + z2 + z3) / 3.0f
        };

        tri.box.min = {minx, miny, minz};
        tri.box.max = {maxx, maxy, maxz};

        mesh.modelData.emplace_back(tri) ;
    }
    mesh.BuildNodeBVH();
    return mesh;
}



