#ifndef EYERLIB_EATRIX_HPP
#define EYERLIB_EATRIX_HPP

#include "EyerCore/EyerCore.hpp"
#define N 3

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
        const Eatrix operator + (const Eatrix & m) {
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
        const Eatrix operator - (const Eatrix & m)
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
        const Eatrix operator * (const float a)
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

        /**
        * float矩阵的逆矩阵
        * @param
        * @return
        */
        Eatrix<float> Inverse ()
        {
            //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
            Eatrix<float> mat_mirror(N, N);
            Eatrix<float> inv_mat(N, N);//最终的逆矩阵（还需要转置）
            float *inv_A_each = new float[N]();//矩阵逆的各列
            //float *B = new float[N*N]();
            float *b = new float[N]();//b阵为B阵的列矩阵分量

            for(int i=0;i<N;i++)
            {
                Eatrix<float> L(N, N);
                Eatrix<float> U(N, N);

                int *P=new int[N]();

                //构造单位阵的每一列
                for(int i=0;i<N;i++)
                {
                    b[i]=0;
                }
                b[i]=1;

                //每次都需要重新将A复制一份
                mat_mirror = mat;

                LUP_Descomposition(mat_mirror,L,U,P);

                inv_A_each=LUP_Solve (L,U,P,b);
                memcpy(inv_A+i*N,inv_A_each,N*sizeof(float));//将各列拼接起来
            }
            inv_A = ~inv_A;           //由于现在根据每列b算出的x按行存储，因此需转置
            return inv_A;


            Eatrix<float> res(row, col);
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

        //逆矩阵  LUP分解
        void LUP_Descomposition(Eatrix<float> & left,Eatrix<float> & up, Eatrix<int> & p)
        {
            int n =GetMatLen();
            int position[100] = {0};

            //初始化position数组
            for (int i = 0; i < n; i++) {
                position[i] = i;
            }

            //定义矩阵a， 并且赋值
            Eatrix<int> a(row, col);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    a.Set(i, j, mat->Get(i,j));

            for (int k = 0; k < n; k++) {
                double max_row_data = -100000;
                int max_row = k;
                for (int i = k; i < n; i++) {
                    if (abs(a[i][k]) > max_row_data) {
                        max_row_data = abs(a[i][k]);
                        max_row = i;
                    }
                }

                if (max_row_data == 0) {
                    printf("this Matrix is singular!");
                    return;
                }

                int tmp = 0;
                tmp = position[k];
                position[k] = position[max_row];
                position[max_row] = tmp;

                for (int i = 0; i < n; i++) {
                    double tmp = 0;
                    tmp = a[k][i];
                    a[k][i] = a[max_row][i];
                    a[max_row][i] = tmp;
                }

                for (int i = k+1; i < n; i++) {
                    a[i][k] /= a[k][k];
                    for (int j = k+1; j < n; j++)
                        a[i][j] -= a[i][k]*a[k][j];
                }
            }

            //给矩阵P赋值
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (j == position[i])
                        p.Set(i, j, 1);
                    else
                        p.Set(i, j, 0);
                }

            //给矩阵left赋值
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (i == j)
                        left.Set(i, j, 1);
                    else if (i > j)
                        left.Set(i, j, a.Get(i, j));
                    else
                        left.Set(i, j, 0);
                }

            //给矩阵up赋值
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (i <= j)
                        up[i][j] = a[i][j];
                    else
                        up[i][j] = 0;
                }

        }

        //逆矩阵  LUP求解方程
        float * LUP_Solve(Eatrix<float> & L,Eatrix<float> & U,int P[N],float b[N])
        {
            float *x=new float[N]();
            float *y=new float[N]();

            //正向替换
            for(int i = 0;i < N;i++)
            {
                y[i] = b[P[i]];
                for(int j = 0;j < i;j++)
                {
                    y[i] = y[i] - L[i*N+j]*y[j];
                }
            }
            //反向替换
            for(int i = N-1;i >= 0; i--)
            {
                x[i]=y[i];
                for(int j = N-1;j > i;j--)
                {
                    x[i] = x[i] - U[i*N+j]*x[j];
                }
                x[i] /= U[i*N+i];
            }
            return x;
        }

    };
}

#endif //EYERLIB_EATRIX_HPP
