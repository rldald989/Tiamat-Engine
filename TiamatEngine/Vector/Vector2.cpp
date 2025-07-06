#include "Vector2.h"

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{

}

Vector2::~Vector2()
{

}

Vector2 Vector2::operator+(const Vector2 &other)
{
    return Vector2(m_x + other.m_x, m_y + other.m_y);
}

Vector2 Vector2::operator+(const float &other)
{
    return Vector2(m_x + other, m_y + other);
}

Vector2 Vector2::operator-(const Vector2 &other)
{
    return Vector2(m_x - other.m_x, m_y - other.m_y);
}

Vector2 Vector2::operator*(const Vector2 &other)
{
    return Vector2(m_x * other.m_x, m_y * other.m_y);
}

Vector2 Vector2::operator/(const Vector2 &other)
{
    return Vector2(m_x / other.m_x, m_y / other.m_y);
}

bool Vector2::operator==(const Vector2 &other) const
{
    return this->m_x == other.m_x && m_y == other.m_y;
}

float Vector2::dot(const Vector2 &other)
{
    return (m_x * other.m_x) + (m_y * other.m_y);
}

float Vector2::det(Vector2 &other)
{
    return (m_x * other.m_x) - (m_y * other.m_y);
}

float Vector2::distance(const Vector2 &a, const Vector2 &b)
{
    return sqrtf(powf(b.m_x - a.m_x, 2) + powf(b.m_y - a.m_y, 2));
}

float Vector2::atan(const Vector2 &a, const Vector2 &b)
{
    return std::atan((b.m_y - a.m_y)/(b.m_x - a.m_x));
}

std::string Vector2::to_string(Vector2 a)
{
    return std::string(std::to_string(a.m_x) + " " + std::to_string(a.m_y));
}

