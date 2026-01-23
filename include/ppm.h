#pragma once
#include <cstdint>
#include <fstream>
#include <filesystem>
#include "color.h"

class PPMFile {
public:
    explicit PPMFile(std::filesystem::path filePath,
                     uint16_t maxColorVal,
                     uint16_t width,
                     uint16_t height);

    PPMFile (const PPMFile& other) = delete ;
    PPMFile& operator= (const PPMFile& other) = delete ;

    void writePixel(const Color& color);
    int  getWidth() const;
    int  getHeight() const;
private:
    void writeHeader(const uint16_t &width,
                     const uint16_t &height,
                     const uint16_t &maxColorValue);

    std::filesystem::path m_filePath;
    uint16_t m_maxColorValue{255};
    uint16_t m_width{}, m_height{};
    std::ofstream m_stream;

};
