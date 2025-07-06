#pragma once

#include "../Vector/Vector2.h"

// x[a c] + y[b d] = [ax + by]
//                   [cx + dy]   

class Matrix2
{
private:
    /* data */
public:
    float a, b, c, d;

    Matrix2(float _a, float _b, float _c, float _d);
    ~Matrix2();

    friend Vector2 operator*(const Vector2& v, const Matrix2& m);
    
    Matrix2 operator*(const Matrix2& other);

    static std::string to_string(Matrix2 composition);

    static float det2(Matrix2 mat2);

    Matrix2 inverse();

    static Vector2 cramer_solve_transform(Matrix2 transformMat, Vector2 transformedCoords);
};