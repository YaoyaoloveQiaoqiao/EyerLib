#include "MBMath.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace MB {
    MBMat::MBMat(int row, int col)
    {
        this->row = row;
        this->col = col;

        init(row, col);
    }

    MBMat::MBMat(const MBMat &m)
    {
        this->row = m.row;
        this->col = m.col;

        init(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    MBMat::~MBMat()
    {
        if (mat != nullptr) {
            for (int i = 0; i < row; i++){
                if (mat[i]) {
                    delete[] mat[i];
                    mat[i] = nullptr;
                }
            }
            if (mat){
                delete[] mat;
            }   
            mat = nullptr;
        }
    }

    MBMat & MBMat::operator = (const MBMat &m)
    {
        if (mat != nullptr) {
            for (int i = 0; i < row; i++){
                if (mat[i]) {
                    delete[] mat[i];
                    mat[i] = nullptr;
                }
            }
            if (mat){
                delete[] mat;
            }
            mat = nullptr;
        }

        row = m.row;
        col = m.col;

        init(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }

        return *this;
    }

    MBMat MBMat::operator + (const MBMat &m) {
        MBMat res(m.row, m.col);
        if (row == m.row && col == m.col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] + m.mat[i][j];
                }
            }
        } 
        else{

        }
        return res;
    }

    MBMat MBMat::operator - (const MBMat &m)
    {
        MBMat res(m.row, m.col);
        if (row == m.row && col == m.col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] - m.mat[i][j];
                }
            }
        } 
        else{

        }

        return res;
    }

    MBMat MBMat::operator * (const MBMat &m)
    {
        MBMat res(row, m.col);
        
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res.mat[i][j] = 0.0f;
            }
        }

        if (m.row != col){

        }
        else {
            for (int i = 0; i < res.row; i++) {
                for (int j = 0; j < res.col; j++) {
                    for (int k = 0; k < res.row; k++) {
                        res.mat[i][j] += mat[i][k] * m.mat[k][j];
                    }
                }
            }
        }
            
        return res;
    }


    MBMat MBMat::operator * (const float a)
    {
        MBMat res(row, col);
        // if (row == row && col == col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] * a;
                }
            }
        // } 
        // else{

        // }

        return res;
    }

    MBMat MBMat::operator ~ ()
    {
        MBMat res(row, col);
        // printf("\n");
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // printf("[%d][%d] ", i, j);
                res.mat[i][j] = mat[j][i];
            }
            // printf("\n");
        }
        return res;
    }

    /*
    SvMat SvMat::operator ! ()
    {
        SvMat res(row, col);

        return res;
    }
    */

    void MBMat::init(int row, int col)
    {
        if (row && col) {
            mat = new float*[row];
            for (int i = 0; i < row; i++) {
                mat[i] = new float[col];
                for (int j = 0; j < col; j++){
                    mat[i][j] = 0;
                    if(i == j){
                        mat[i][j] = 1;
                    }
                }
            }
        }
    }

    void MBMat::output() {
        printf("output:(%d,%d)\n", row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++){
                printf(" %.2f ", mat[i][j]);
            }
            printf("\n");
        }
    }

    int MBMat::Print()
    {
        output();
        return 0;
    }

    int MBMat::GetMatLen()
    {
        return this->col * this->row * sizeof(float);
    }

    float * MBMat::GetMat(float * matBuffer)
    {
        if(matBuffer == NULL) {
            matBuffer = (float *)malloc(GetMatLen());
        }

        // memset(matBuffer, 0, GetMatLen());

        int index = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++){
                matBuffer[index] = mat[i][j];
                index++;
            }
        }

        return matBuffer;
    }
}