#pragma once
#include <mathUtils.h>

struct Camera {
    const Vec3<float> origin{0, 0, -10};
    int  width ;
    int  height ;
    float focalLength{-9.0f}; // this is basically the  distance of the image plane from camera towards negative z axis
                              // focal length of positive 3 value means image plane is 3 units in front of camera along positive z axis

    Camera(const int& width , const int& height, const float& fl = 1.0 ): width(width), height(height) {
        focalLength = fl;
    }
    [[nodiscard]] float getNDCx( const int i) const {
        return ((static_cast<float>(i) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
    }
    [[nodiscard]] float getNDCy( const int j) const {
        return ((static_cast<float>(j) + 0.5f) / static_cast<float>(height)) * 2.0f - 1.0f;
    }

};
