#include "Matrix3.h"

Matrix3::Matrix3(Vector3 _rowA, Vector3 _rowB, Vector3 _rowC) : 
rowA(_rowA),
rowB(_rowB),
rowC(_rowC)
{
    
}

Matrix3::~Matrix3()
{
}

Vector3 operator*(const Vector3 &v, const Matrix3 &m)
{
    return Vector3(
        (m.rowA.x * v.x) + (m.rowA.y * v.y) + (m.rowA.z * v.z), 
        (m.rowB.x * v.x) + (m.rowB.y * v.y) + (m.rowB.z * v.z), 
        (m.rowC.x * v.x) + (m.rowC.y * v.y) + (m.rowC.z * v.z));
}

Matrix3 Matrix3::operator*(const Matrix3 &other)
{

    Vector3 columnA(other.rowA.x, other.rowB.x, other.rowC.x);
    Vector3 columnB(other.rowA.y, other.rowB.y, other.rowC.y);
    Vector3 columnC(other.rowA.z, other.rowB.z, other.rowC.z);

    Vector3 resultA(columnA * *this);
    Vector3 resultB(columnB * *this);
    Vector3 resultC(columnC * *this);

    Matrix3 reOrdered(
        Vector3(resultA.x, resultB.x, resultC.x),
        Vector3(resultA.y, resultB.y, resultC.y),
        Vector3(resultA.z, resultB.z, resultC.z)
    );

    return reOrdered;
}

std::string Matrix3::to_string(Matrix3 composition)
{
    return std::string(
      "[" + Vector3::to_string_f(composition.rowA) + "]\n" +
    + "[" + Vector3::to_string_f(composition.rowB) + "]\n"
    + "[" + Vector3::to_string_f(composition.rowC) + "]\n");
}

float Matrix3::det3(Matrix3 mat3)
{
    Matrix2 a(mat3.rowB.y, mat3.rowB.z, mat3.rowC.y, mat3.rowC.z);
    Matrix2 b(mat3.rowB.x, mat3.rowB.z, mat3.rowC.x, mat3.rowC.z);
    Matrix2 c(mat3.rowB.x, mat3.rowB.y, mat3.rowC.x, mat3.rowC.y);
    return (mat3.rowA.x * Matrix2::det2(a)) - (mat3.rowA.y * Matrix2::det2(b)) + (mat3.rowA.z * Matrix2::det2(c));
}

Vector3 Matrix3::cramer_solve_transform(Matrix3 transformMat, Vector3 transformedCoords)
{
    float x = det3(
        Matrix3(
            Vector3(transformedCoords.x, transformMat.rowA.y, transformMat.rowA.z),
            Vector3(transformedCoords.y, transformMat.rowB.y, transformMat.rowB.z),
            Vector3(transformedCoords.z, transformMat.rowC.y, transformMat.rowC.z)
        )
    ) / det3(transformMat);

    float y = det3(
        Matrix3(
            Vector3(transformMat.rowA.x, transformedCoords.x, transformMat.rowA.z),
            Vector3(transformMat.rowB.x, transformedCoords.y,  transformMat.rowB.z),
            Vector3(transformMat.rowC.x, transformedCoords.z,  transformMat.rowC.z)
        )
    ) / det3(transformMat);

    float z = det3(
        Matrix3(
            Vector3(transformMat.rowA.x, transformMat.rowA.y, transformedCoords.x),
            Vector3(transformMat.rowB.x, transformMat.rowB.y, transformedCoords.y),
            Vector3(transformMat.rowC.x, transformMat.rowC.y, transformedCoords.z)
        )
    ) / det3(transformMat);

    return Vector3(x, y, z);
}