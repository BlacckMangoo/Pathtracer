#pragma once
#include <color.h>
struct Material {
    float reflectivity = 0.0f ;
    Color baseColor = Colors::white;
};

namespace  Materials {

    constexpr Material gold = {
        .reflectivity = 0.6f,
        .baseColor = Colors::yellow,
    };

    constexpr Material plastic = {
        .reflectivity = 0.2f,
        .baseColor = Colors::lightGray,
    };

    constexpr Material glass = {
        .reflectivity = 0.9f,
        .baseColor = Colors::cyan,
    };

    constexpr Material emerald = {
        .reflectivity = 0.4f,
        .baseColor = Colors::green,
    };
}

