#include "MBMath.hpp"

namespace MB {
    MBMat3x1::MBMat3x1() : MBMat(3, 1)
    {

    }

    MBMat3x1::~MBMat3x1()
    {

    }

    float MBMat3x1::x()
    {
        return mat[0][0];
    }

    float MBMat3x1::y()
    {
        return mat[1][0];
    }

    float MBMat3x1::z()
    {
        return mat[2][0];
    }

    int MBMat3x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int MBMat3x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }

    int MBMat3x1::SetZ(float z)
    {
        mat[2][0] = z;
        return 0;
    }
}