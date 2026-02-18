#pragma once
#include <mathUtils.h>

struct Camera {
    const Vec3<float> origin{0.0f, 0.0f, 15.0f};
    int  width ;
    int  height ;
    float focalLength{1.0f};    // this is basically the modulus of distance of image plane from camera origin

    //camera is at origin looking towards -z axis

    Camera(const int& width , const int& height, const float& fl = 1.0f ): width(width), height(height) , focalLength(fl) {};
    [[nodiscard]] float getNDCx( const int i) const {
        return ((static_cast<float>(i) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
    }
    [[nodiscard]] float getNDCy( const int j) const {
        return ((static_cast<float>(j) + 0.5f) / static_cast<float>(height)) * 2.0f - 1.0f;
    }

};
