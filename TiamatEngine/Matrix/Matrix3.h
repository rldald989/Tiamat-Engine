#pragma once

#include "../Vector/Vector3.h"
#include "../Matrix/Matrix2.h"

class Matrix3
{
private:
public:    
    Vector3 rowA;
    Vector3 rowB;
    Vector3 rowC;

    Matrix3(Vector3 _rowA, Vector3 _rowB, Vector3 _rowC);
    ~Matrix3();

    friend Vector3 operator*(const Vector3& v, const Matrix3& m);

    Matrix3 operator*(const Matrix3& other);

    static std::string to_string(Matrix3 composition);

    static float det3(Matrix3 mat3);

    static Vector3 cramer_solve_transform(Matrix3 transformMat, Vector3 transformedCoords);
};