#pragma once
#include <color.h>
struct Material {
    Color baseColor = Colors::white;
};

namespace  Materials {
    constexpr Material gold = {.baseColor = Colors::yellow,};
    constexpr Material glass = {.baseColor = Colors::cyan,};
}

