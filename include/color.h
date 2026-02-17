#pragma once
#include <mathUtils.h>
struct Color {
    float r{0.0f};
    float g{0.0f};
    float b{0.0f};
    Color operator*(const float s) const {return { r * s, g * s, b * s };}
    Color operator+(const Color& other) const {return { r + other.r, g + other.g, b + other.b };}
    Color operator*(const Color& other) const {return { r * other.r, g * other.g, b * other.b };}
    Color operator*(const Vec3<float> other) const { return { r * other.x, g * other.y, b * other.z };}
    Color& operator=(const float s) { r = s; g = s; b = s; return *this;  }

    Color operator/(const float pdf) const { return { r / pdf, g / pdf, b / pdf }; }
};


namespace Colors {

    constexpr Color black{0.0f, 0.0f, 0.0f};
    constexpr Color white{1.0f, 1.0f, 1.0f};
    constexpr Color red{1.0f, 0.0f, 0.0f};
    constexpr Color green{0.0f, 1.0f, 0.0f};
    constexpr Color yellow{1.0f, 1.0f, 0.0f};
    constexpr Color blue{0.0f, 0.0f, 1.0f};
    constexpr Color cyan{0.0f, 1.0f, 1.0f};
    constexpr Color magenta{1.0f, 0.0f, 1.0f};
    constexpr Color gray{0.5f, 0.5f, 0.5f};
    constexpr Color darkGray{0.25f, 0.25f, 0.25f};
    constexpr Color lightGray{0.75f, 0.75f, 0.75f};
    constexpr Color orange{1.0f, 0.647f, 0.0f};
    constexpr Color purple{0.502f, 0.0f, 0.502f};
    constexpr Color brown{0.647f, 0.165f, 0.165f};
    constexpr Color pink{1.0f, 0.753f, 0.796f};
    constexpr Color skyBlue{0.529f, 0.808f, 0.922f};
}
