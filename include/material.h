#pragma once
#include <color.h>
struct Material {
    Color baseColor = Colors::white;
    float reflectance = 0.5f;
};

namespace  Materials {
    constexpr Material gold = {.baseColor = Colors::yellow,.reflectance = 0.5f};
    constexpr Material glass = {.baseColor = Colors::cyan,.reflectance = 0.7f};
}

