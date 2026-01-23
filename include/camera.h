#pragma once
#include <mathUtils.h>

struct Camera {
    const Vec3<float> origin{0, 0, 0};
    int  width ;
    int  height ;
    float focalLength{-1.0f};

    Camera(const int& width , const int& height, const float& fl = -1.0 ): width(width), height(height) {
    }
    [[nodiscard]] float getNDCx( const int i) const {
        return ((static_cast<float>(i) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
    }
    [[nodiscard]] float getNDCy( const int j) const {
        return ((static_cast<float>(j) + 0.5f) / static_cast<float>(height)) * 2.0f - 1.0f;
    }

};
