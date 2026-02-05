#pragma once
struct Color {
    float r{0.0f};
    float g{0.0f};
    float b{0.0f};
    Color operator*(const float s) const {return { r * s, g * s, b * s };}
    Color operator+(const Color& other) const {return { r + other.r, g + other.g, b + other.b };}
};


namespace Colors {

    constexpr Color black{2.0f / 255.0f, 2.0f / 255.0f, 2.0f / 255.0f};
    constexpr Color white{1.0f, 1.0f, 1.0f};
    constexpr Color red{1.0f, 0.0f, 0.0f};
    constexpr Color green{0.0f, 1.0f, 0.0f};
    constexpr Color yellow{1.0f, 1.0f, 0.0f};
    constexpr Color blue{0.0f, 0.0f, 1.0f};
    constexpr Color cyan{0.0f, 1.0f, 1.0f};
    constexpr Color magenta{1.0f, 0.0f, 1.0f};
    constexpr Color gray{128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f};
    constexpr Color darkGray{64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f};
    constexpr Color lightGray{192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f};
    constexpr Color orange{1.0f, 165.0f / 255.0f, 0.0f};
    constexpr Color purple{128.0f / 255.0f, 0.0f, 128.0f / 255.0f};
    constexpr Color brown{165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f};
    constexpr Color pink{1.0f, 192.0f / 255.0f, 203.0f / 255.0f};
    constexpr Color skyBlue{135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f};
}
