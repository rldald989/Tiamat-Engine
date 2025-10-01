#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const float& other)
{
    return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator-(const Vector3 &other)
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const float &other)
{
    return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator*(const Vector3 &other)
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float &other)
{
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const Vector3 &other)
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(const float& other)
{
    return Vector3(x / other, y / other, z / other);
}

bool approximateEq(float a, float b, float tolerance){
    return fabs(a - b) < tolerance;
}

bool Vector3::operator==(const Vector3 &other) const
{
    return (approximateEq(x, other.x, 1.01f) && approximateEq(y, other.y, 1.01f) && approximateEq(z, other.z, 1.01f));
}

float Vector3::dot(Vector3 &other)
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3 Vector3::cross(Vector3 &other)
{
    return Vector3(
        (y * other.z) - (other.y * z), 
        (z * other.x) - (other.z * x),
        (x * other.y) - (other.x - y)
    );
}

Vector3 Vector3::rand()
{
    return Vector3(float(std::rand() % 100)/ 100, float(std::rand() % 100)/ 100, float(std::rand() % 100)/ 100);
}

Vector3 Vector3::sqrt(const Vector3 &a)
{
    return Vector3(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z));
}

Vector3 Vector3::mix(Vector3& a, Vector3& b, float mod)
{
    return a * (1.f - mod) + b * mod;
}

Vector3 Vector3::lerp(Vector3 a, Vector3 b, float t)
{
    return Vector3(a + (b - a) * t);
}

float* Vector3::vector3_to_float(Vector3 v)
{
    static float arr[3];
    arr[0] = v.x;
    arr[1] = v.y;
    arr[2] = v.z;
    return arr;
}

std::string Vector3::to_string_f(Vector3 a)
{
    return std::string(std::to_string(a.x) + " " + std::to_string(a.y) + " " + std::to_string(a.z));
}

std::string Vector3::to_string_i(Vector3 a)
{
    return std::string(std::to_string((int)a.x) + " " + std::to_string((int)a.y) + " " + std::to_string((int)a.z));
}

Vector3 Vector3::to_rgb(Vector3 a)
{
    return Vector3(a.x, a.y, a.z) * 255;
}

Vector3 Vector3::to_xyz(Vector3 a)
{
    return a/255;
}
