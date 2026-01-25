#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <primitives.h>
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
    explicit ModelFileParser( const std::filesystem::path& modelFilePath , std::vector<Triangle>& triangles) {
        ifStream = std::ifstream(modelFilePath,std::ios::in);
        if (!ifStream.is_open()) {
            throw std::runtime_error("Failed to open model file: " + modelFilePath.string());
        }
        // read number of vertices
        ifStream >> m_noOfTriangles;
        std::cout << "Number of vertices in model file: " << m_noOfTriangles << "\n";
        // read triangles
        for (size_t i = 0; i < m_noOfTriangles; ++i) {
            float x1, y1, z1;
            float x2, y2, z2;
            float x3, y3, z3;
            ifStream >> x1 >> y1 >> z1;
            ifStream >> x2 >> y2 >> z2;
            ifStream >> x3 >> y3 >> z3;
            // skip blank line
            ifStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            triangles.emplace_back(
                Vec3<float>(x1, y1, z1),
                Vec3<float>(x2, y2, z2),
                Vec3<float>(x3, y3, z3)
            );
        }
    }
    size_t m_noOfTriangles {};
private:
    std::ifstream ifStream;
};