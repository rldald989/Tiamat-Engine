#pragma once

#include <string>
#include <cmath>

class Vector2
{
private:
    
public:
    Vector2(float x, float y);
    ~Vector2();

    float m_x;
    float m_y;

    Vector2 operator+(const Vector2& other);
    Vector2 operator+(const float& other);
    Vector2 operator-(const Vector2& other);
    Vector2 operator-(const float& other);
    Vector2 operator*(const Vector2& other);
    Vector2 operator*(const float& other);
    Vector2 operator/(const Vector2& other);
    Vector2 operator/(const float& other);
    bool operator==(const Vector2& other) const;

    static Vector2 lerp(Vector2& a, Vector2& b, float t);
    static Vector2 querp(Vector2& a, Vector2& b, Vector2& c, float t);

    float dot(const Vector2& other);
    float det(Vector2& other);

    static float distance(const Vector2& a, const Vector2&b);
    static float atan(const Vector2& a, const Vector2& b);

    static std::string to_string(Vector2 a);
};

namespace std {
    template <>
    struct hash<Vector2> {
        std::size_t operator()(const Vector2& v) const {
            return std::hash<int>()(v.m_x) ^ (std::hash<int>()(v.m_y) << 1);
        }
    };
}