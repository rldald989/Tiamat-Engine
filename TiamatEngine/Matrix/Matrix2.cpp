#include "Matrix2.h"

Matrix2::Matrix2(float _a, float _b, float _c, float _d): a(_a), b(_b), c(_c), d(_d)
{
}

Matrix2::~Matrix2()
{
}

Vector2 operator*(const Vector2 &v, const Matrix2 &m)
{
    return Vector2((m.a * v.m_x) + (m.b * v.m_y), (m.c * v.m_x) + (m.d * v.m_y));
}

Matrix2 Matrix2::operator*(const Matrix2 &other)
{
    Vector2 ac(other.a, other.c);
    Vector2 bd(other.b, other.d);
    Vector2 resultA = ac * *this;
    Vector2 resultB = bd * *this;
    return Matrix2(resultA.m_x, resultB.m_x, resultA.m_y, resultB.m_y);
}

std::string Matrix2::to_string(Matrix2 composition)
{
    return std::string(
      "[" + Vector2::to_string(Vector2(composition.a, composition.b)) + "]\n" +
    + "[" + Vector2::to_string(Vector2(composition.c, composition.d)) + "]\n");
}

float Matrix2::det2(Matrix2 mat2)
{
    return (mat2.a * mat2.d) - (mat2.b * mat2.c);
}

Matrix2 Matrix2::inverse()
{
    float detAp = det2(*this);
    Matrix2 result = Matrix2(d / detAp, -b / detAp, -c / detAp, a / detAp);
    return result;
}

Vector2 Matrix2::cramer_solve_transform(Matrix2 transformMat, Vector2 transformedCoords)
{
    float y = det2(Matrix2(transformMat.a, transformedCoords.m_x, transformMat.c, transformedCoords.m_y)) / det2(transformMat);
    float x = det2(Matrix2(transformedCoords.m_x, transformMat.b, transformedCoords.m_y, transformMat.d)) / det2(transformMat);
    return Vector2(x, y);
}