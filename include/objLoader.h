#pragma once
#include "tinyObj.h"
#include <filesystem>
#include <vector>
#include <string>
#include <primitives.h>

class ObjLoader {
public:
    explicit ObjLoader(const std::filesystem::path& objFilePath);

    [[nodiscard]] bool isLoaded() const { return loaded; }
    [[nodiscard]] std::vector<Triangle> LoadMesh() const;

private:
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    bool loaded = false;
    std::string warn;
    std::string err;
};