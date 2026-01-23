#pragma once
#include <iostream>
#include <cmath>
#include <optional>
#include <utility>
#include <type_traits>
#include <limits>
#include <cassert>

template <typename T>
struct Vec3 {
    static_assert(std::is_floating_point_v<T>, "Vec3 should be used with a floating-point type");

    T x{}, y{}, z{};
    // Default and value constructors
    constexpr Vec3() noexcept = default;
    constexpr Vec3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}
    explicit constexpr Vec3(T v) noexcept : x(v), y(v), z(v) {}

    constexpr Vec3 operator-() const noexcept { return {-x, -y, -z}; }

    constexpr Vec3 operator+(const Vec3& other) const noexcept {
        return {x + other.x, y + other.y, z + other.z};
    }
    constexpr Vec3& operator+=(const Vec3& other) noexcept {
        x += other.x; y += other.y; z += other.z; return *this;
    }

    constexpr Vec3 operator-(const Vec3& other) const noexcept {
        return {x - other.x, y - other.y, z - other.z};
    }
    constexpr Vec3& operator-=(const Vec3& other) noexcept {
        x -= other.x; y -= other.y; z -= other.z; return *this;
    }

    constexpr Vec3 operator*(T scalar) const noexcept {
        return {x * scalar, y * scalar, z * scalar};
    }
    friend constexpr Vec3 operator*(T scalar, const Vec3& v) noexcept {
        return {v.x * scalar, v.y * scalar, v.z * scalar};
    }
    constexpr Vec3& operator*=(T scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }

    constexpr Vec3 operator/(T scalar) const noexcept {
        return {x / scalar, y / scalar, z / scalar};
    }
    constexpr Vec3& operator/=(T scalar) noexcept { x /= scalar; y /= scalar; z /= scalar; return *this; }

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
        os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

    [[nodiscard]] constexpr T dot(const Vec3& other) const noexcept {
        return x * other.x + y * other.y + z * other.z;
    }
    [[nodiscard]] constexpr Vec3<T> cross(const Vec3& other) const noexcept {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    [[nodiscard]] T length() const noexcept {
        using std::sqrt;
        return static_cast<T>(sqrt(static_cast<long double>(x * x + y * y + z * z)));
    }
    [[nodiscard]] Vec3 normalized() const noexcept {
        const T len = length();
        const T eps = std::numeric_limits<T>::epsilon();
        if (len <= eps) {
            return Vec3{static_cast<T>(0)}; // avoid division by zero
        }
        return *this / len;
    }

    constexpr bool operator==(const Vec3& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }
    constexpr bool operator!=(const Vec3& other) const noexcept { return !(*this == other); }

};

//quadratic Ax^2 + Bx + C = 0
// if A is very small, treat as linear equation
///Bx + C = 0
template <typename T>
inline std::optional<std::pair<T,T>> findRootsOfQuadratic(T a, T b, T c) {

    static_assert(std::is_floating_point_v<T>, "findRootsOfQuadratic requires a floating-point type");
    const T eps = std::numeric_limits<T>::epsilon();
    if (std::abs(a) <= eps) {
        if (std::abs(b) <= eps) {
            return std::nullopt;
        }
        T t = -c / b;
        return std::make_pair(t, t);
    }
    const T discriminant = b * b - static_cast<T>(4) * a * c;
    if (discriminant < static_cast<T>(0)) {
        return std::nullopt;
    }

    const T sqrtDisc = static_cast<T>(std::sqrt(static_cast<long double>(discriminant)));
    T t1 = (-b - sqrtDisc) / (static_cast<T>(2) * a);
    T t2 = (-b + sqrtDisc) / (static_cast<T>(2) * a);
    return std::make_pair(t1, t2);
}