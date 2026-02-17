#pragma once
#include <color.h>

struct Material {
    Color  albedo = {0.8f, 0.8f, 0.8f};
    Color  emission = {0.0f, 0.0f, 0.0f};
    float roughness = 0.5f;
    float metallic = 0.0f;

    [[nodiscard]] bool isEmissive() const {
        return emission.r > 0.0f || emission.g > 0.0f || emission.b > 0.0f;
    }
};

namespace  Materials {
    constexpr Material gold{
        { 1.0f, 0.843f, 0.0f },
        {0.0f, 0.0f, 0.0f},
        0.2f,
        1.0f,
    };
    constexpr Material silver{
        {0.75f, 0.75f, 0.75f},
        {0.0f, 0.0f, 0.0f},
        0.2f,
        1.0f,
    };
    constexpr Material glass{
        {0.9f, 0.9f, 0.9f},
        {0.0f, 0.0f, 0.0f},
        0.0f,
        0.0f,
    };
    constexpr Material diffuseWhite{
        {0.8f, 0.8f, 0.8f},
        {0.0f, 0.0f, 0.0f},
        1.0f,
        0.0f,
    };
    constexpr Material diffuseRed{
        {0.8f, 0.2f, 0.2f},
        {0.0f, 0.0f, 0.0f},
        1.0f,
        0.0f,
    };
    constexpr Material diffuseGreen{
        {0.2f, 0.8f, 0.2f},
        {0.0f, 0.0f, 0.0f},
        1.0f,
        0.0f,
    };
    constexpr Material diffuseBlue{
        {0.2f, 0.2f, 0.8f},
        {0.0f, 0.0f, 0.0f},
        1.0f,
        0.0f,
    };

    constexpr Material glowingPink{
        {1.0f, 0.753f, 0.796f},
        {5.0f, 5.0f, 5.0f},
        1.0f,
        0.0f,
    };
    constexpr Material light{
        {0.0f, 0.0f, 0.0f},
        {10.0f, 10.0f, 10.0f},
        1.0f,
        0.0f,
    };

}

