#include "MBMath.hpp"

namespace MB {
    MBMat2x1::MBMat2x1() : MBMat(2, 1)
    {

    }

    MBMat2x1::MBMat2x1(const MBMat & m) : MBMat(2, 1)
    {
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = 0.0f;
            }
        }
        
        if(this->row != m.row){
            return;
        }
        if(this->col != m.col){
            return;
        }

        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    MBMat2x1::MBMat2x1(float x, float y) : MBMat(2, 1)
    {
        SetX(x);
        SetY(y);
    }

    MBMat2x1::~MBMat2x1()
    {

    }

    float MBMat2x1::x()
    {
        return mat[0][0];
    }

    float MBMat2x1::y()
    {
        return mat[1][0];
    }

    int MBMat2x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int MBMat2x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }
}