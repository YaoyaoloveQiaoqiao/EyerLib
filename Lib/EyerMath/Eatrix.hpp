#ifndef EYERLIB_EATRIX_HPP
#define EYERLIB_EATRIX_HPP

#include "EyerCore/EyerCore.hpp"
#include<cmath>
#include<algorithm>

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
        Eatrix(const Eatrix & m)
        {
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
        const Eatrix operator + (const Eatrix & m) const
        {
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
        const Eatrix operator - (const Eatrix & m) const
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
        const Eatrix operator * (const Eatrix &m) const
        {
            Eatrix res(row, m.col);
            for (int i = 0; i < res.row; i++) {
                for (int j = 0; j < res.col; j++) {
                    res.mat[i][j] = 0.0f;
                }
            }
            if (m.row == col) {
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
        const Eatrix operator * (const float a) const
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
        const Eatrix operator ~ () const
        {
            Eatrix res(row, col);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[j][i];
                }
            }
            return res;
        }

        /**
        * float矩阵的逆矩阵
         * 注意：目前只有3*3矩阵求逆测试通过
        * @param
        * @return
        */
        Eatrix operator ! ()
        {
            Eatrix inv_matrix(row, col);

            //初始化
            Eatrix l(row, col);
            Eatrix u(row, col);
            Eatrix c(row, col);
            Eatrix ad_l(row, col);
            Eatrix ad_u(row, col);

            //LU分解
            for (int i = 0; i < row - 1; i++)
            {
                for (int j = i; j < row; j++)
                {
                     T tem = 0;
                    for (int k = 0; k < i; k++)
                        tem += l.Get(i, k) * u.Get(k, j);
                    u.Set(i, j, Get(i, j) - tem);
                }
                for (int j = i + 1; j < row; j++)
                {
                     T tem = 0;
                    for (int k = 0; k < i; k++)
                        tem += l.Get(j, k) * u.Get(k, i);
                    l.Set(j, i, (Get(j, i) - tem) / u.Get(i, i));
                }
            }
            u.Set(row - 1, row - 1, Get(row - 1, row - 1));
            for (int i = 0; i < row - 1; i++){
                 T tem = u.Get(row - 1, row - 1) - (l.Get(row - 1, i) * u.Get(i, row - 1));
                u.Set(row - 1, row - 1, tem);
            }

            //U的逆矩阵
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    if (i > j) ad_u.Set(i, j, 0);
                    else if (i == j)
                    {
                        ad_u.Set(i, j, 1);
                        for (int k = 0; k < row; k++)
                            if (k != j){
                                 T tem = ad_u.Get(i, j) * u.Get(k, k);
                                ad_u.Set(i, j, tem);
                            }
                    }
                    else if (j - i == 1)
                    {
                         T tem = ad_u.Get(i, j) - u.Get(i, j);
                        ad_u.Set(i, j, tem);
                        for (int k = 0; k < row; k++)
                            if (k != i && k != j){
                                 T tem = ad_u.Get(i, j) * u.Get(k, k);
                                ad_u.Set(i, j, tem);
                            }
                    }
                    else if (j - i >= 2)
                    {
                         T deltas_aii = 1;
                        for (int k = 0; k < row; k++)
                            if (k < i || k > j)
                                deltas_aii *= u.Get(k, k);
                        int permutation[row];
                        for (int t = 0; t < j - i; t++) permutation[t] = i + t + 1;
                         T sum = 0;
                        do
                        {
                            int cnt = 0;
                            for (int t2 = 0; t2 < j - i; t2++)
                                for (int t3 = t2; t3 < j - i; t3++)
                                    if (permutation[t3] < permutation[t2]) cnt++;
                             T mul = 1;
                            for (int t1 = i; t1 < j; t1++)
                                mul *= u.Get(t1, permutation[t1 - i]);
                            if ((j - i + 1) % 2 == 0)mul *= -1;
                            if (cnt % 2 == 0) sum += mul;
                            else sum -= mul;
                        } while (std::next_permutation(permutation, permutation + j - i));
                        ad_u.Set(i, j, sum * deltas_aii);
                    }
                }
            }
             T det_u = 1;
            for (int k = 0; k < row; k++) det_u *= u.Get(k, k);
            if (det_u < 1e-16)
            {
                printf("矩阵不可逆，请检查输入！\n");
                return inv_matrix;
            }
            for (int i = 0; i < row; i++)
                for (int j = 0; j < row; j++){
                     T tem = ad_u.Get(i, j) / det_u;
                    ad_u.Set(i, j, tem);
                }


            //l的逆矩阵
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    if (i < j) ad_l.Set(i, j, 0);
                    else if (i == j)
                    {
                        ad_l.Set(i, j, 1);
                        for (int k = 0; k < row; k++)
                            if (k != j){
                                 T tem = ad_l.Get(i, j) * l.Get(k, k);
                                ad_l.Set(i, j, tem);
                            }
                    }
                    else if (i - j == 1)
                    {
                        ad_l.Set(i, j, -l.Get(i, j));
                        for (int k = 0; k < row; k++)
                            if (k != i && k != j){
                                 T tem = ad_l.Get(i, j) * l.Get(k, k);
                                ad_l.Set(i, j, tem);
                            }
                    }
                    else if (i - j >= 2)
                    {
                         T deltas_aii = 1;
                        for (int k = 0; k < row; k++)
                            if (k < i || k > j)
                                deltas_aii *= l.Get(i, i);
                        int permutation[row];
                        for (int t = 0; t < i - j; t++) permutation[t] = j + t + 1;
                         T sum = 0;
                        do
                        {
                            int cnt = 0;
                            for (int t2 = 0; t2 < i - j; t2++)
                                for (int t3 = t2; t3 < i - j; t3++)
                                    if (permutation[t3] < permutation[t2]) cnt++;
                             T mul = 1;
                            for (int t1 = j; t1 < i; t1++)
                                mul *= l.Get(permutation[t1 - j], t1);
                            if ((i - j + 1) % 2 == 0)mul *= -1;
                            if (cnt % 2 == 0) sum += mul;
                            else sum -= mul;
                        } while (std::next_permutation(permutation, permutation + i - j));
                        ad_l.Set(i, j, sum * deltas_aii);
                    }
                }
            }
             T det_l = 1;
            for (int k = 0; k < row; k++) det_l *= l.Get(k, k);
            if (det_u < 1e-16)
            {
                printf("矩阵不可逆，请检查输入！\n");
                return inv_matrix;
            }
            for (int i = 0; i < row; i++)
                for (int j = 0; j < row; j++){
                     T tem = ad_l.Get(i, j) / det_l;
                    ad_l.Set(i, j, tem);
                }

            inv_matrix = ad_u * ad_l;
            return inv_matrix;
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
                    str += EyerString::Number(mat[i][j], " %.4f ");
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
