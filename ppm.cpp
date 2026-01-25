#include "ppm.h"
#include <fstream>
#include <stdexcept>



PPMFile::PPMFile(std::filesystem::path filePath,uint16_t maxColorVal,uint16_t width,uint16_t height)
    : m_filePath(std::move(filePath)),
      m_maxColorValue(maxColorVal),
      m_width(width),
      m_height(height)
{
    std::ofstream file(m_filePath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + m_filePath.string());
    }

    file << "P6\n";
    file << m_width << " " << m_height << "\n";
    file << m_maxColorValue << "\n";

    // keep file open by swapping
    m_stream.swap(file);
}

void PPMFile::writePixel(const Color& color) {
    unsigned char pixel[3] = {
        static_cast<unsigned char>(color.r),
        static_cast<unsigned char>(color.g),
        static_cast<unsigned char>(color.b)
    };
    m_stream.write(reinterpret_cast<char*>(pixel), 3);
}

int  PPMFile::getWidth() const {
    return m_width;
}

int  PPMFile::getHeight() const {
    return m_height;
}
