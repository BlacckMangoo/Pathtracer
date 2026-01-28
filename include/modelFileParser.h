#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <primitives.h>
#include <bvh.h>

struct Mesh {
    std::vector<Triangle> modelData = {};
    BVH bvh{};
    void BuildNodeBVH() {
        if (modelData.empty()) std::cerr << "BuildNodeBVH failed: no model data" << std::endl;
        bvh.rootIndex = bvh.BuildBVH( 0, static_cast<int>(modelData.size()), modelData );
    }
};

// file format

// LINE 1  -> number of triangles (uint16_t)
//BLANK
// LINE 2 -> vertex 1 x y z (float float float)
// LINE 3 -> vertex 2 x y z (float float float)
// LINE 4 -> vertex 3 x y z (float float float)
//BLANK

// each 3 lines define a triangle


class ModelFileParser {
public:
    explicit ModelFileParser( const std::filesystem::path& modelFilePath , Mesh& mesh );
    size_t m_noOfTriangles {};
    std::ifstream ifStream;

private:
    void ConstructMeshFromFile( Mesh& mesh );
};