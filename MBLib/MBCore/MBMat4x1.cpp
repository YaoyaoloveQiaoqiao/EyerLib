#include "MBMath.hpp"

namespace MB {
    MBMat4x1::MBMat4x1() : MBMat(4, 1)
    {

    }

    MBMat4x1::~MBMat4x1()
    {

    }

    float MBMat4x1::x()
    {
        return mat[0][0];
    }

    float MBMat4x1::y()
    {
        return mat[1][0];
    }

    float MBMat4x1::z()
    {
        return mat[2][0];
    }

    float MBMat4x1::w()
    {
        return mat[3][0];
    }

    int MBMat4x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int MBMat4x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }

    int MBMat4x1::SetZ(float z)
    {
        mat[2][0] = z;
        return 0;
    }

    int MBMat4x1::SetW(float w)
    {
        mat[3][0] = w;
        return 0;
    }
}