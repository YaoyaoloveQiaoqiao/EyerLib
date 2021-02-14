#ifndef EYERLIB_EATRIX_HPP
#define EYERLIB_EATRIX_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    template<typename T>
    class Eatrix {
    public:
        Eatrix(int _row = 0, int _col = 0)
        {
            Resize(_row, _col);
        }

        ~Eatrix()
        {
            free();
        }

        int Resize(int _row, int _col)
        {
            free();

            row = _row;
            col = _col;

            init(row, col);
            return 0;
        }

        const T Get(int y, int x) const
        {
            return mat[y][x];
        }

        int Set(int y, int x, T t)
        {
            mat[y][x] = t;
            return 0;
        }

        /*
         * 拷贝
         */
        Eatrix(const Eatrix & m){
            *this = m;
        }

        /*
         * 赋值运算符
         */
        const Eatrix & operator = (const Eatrix & m)
        {
            free();

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

        /**
         * 加法
         * @param m
         * @return
         */
        Eatrix operator + (const Eatrix & m) {
            Eatrix res(m.row, m.col);
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

        /**
         * 减法
         * @param m
         * @return
         */
        Eatrix operator - (const Eatrix & m)
        {
            Eatrix res(m.row, m.col);
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

        /**
         * 矩阵乘法
         * @param m
         * @return
         */
        Eatrix operator * (const Eatrix &m)
        {
            Eatrix res(row, m.col);
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

        /**
         * 矩阵数乘
         * @param a
         * @return
         */
        Eatrix operator * (const float a)
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] * a;
                }
            }
            return res;
        }

        /**
         * 矩阵转置
         * @param
         * @return
         */
        Eatrix operator ~ ()
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[j][i];
                }
            }
            return res;
        }


        int SetData(T * arr, int len)
        {
            int index = 0;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++){
                    if(index < len){
                        mat[i][j] = arr[index];
                    }
                    index++;
                }
            }
            return 0;
        }

        const int PrintInfo() const
        {
            EyerLog("output:(%d,%d)\n", row, col);
            for (int i = 0; i < row; i++) {
                EyerString str = "";
                for (int j = 0; j < col; j++){
                    str = str + EyerString::Number(mat[i][j], " %.4f ");
                }
                EyerLog("%s\n", str.str);
            }
            return 0;
        }

        int GetMatLen()
        {
            return this->col * this->row * sizeof(float);
        }

        T * GetMat(T * matBuffer)
        {
            if(matBuffer == NULL) {
                matBuffer = (float *)malloc(GetMatLen());
            }

            int index = 0;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++){
                    matBuffer[index] = mat[i][j];
                    index++;
                }
            }

            return matBuffer;
        }

    public:
        int row = 0;
        int col = 0;
        T * * mat = nullptr;

    private:
        void init(int row, int col)
        {
            if (row && col) {
                mat = new T * [row];
                for (int i = 0; i < row; i++) {
                    mat[i] = new T[col];
                    for (int j = 0; j < col; j++){
                        mat[i][j] = 0;
                        if(i == j){
                            mat[i][j] = 1;
                        }
                    }
                }
            }
        }

        void free()
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
    };
}

#endif //EYERLIB_EATRIX_HPP
