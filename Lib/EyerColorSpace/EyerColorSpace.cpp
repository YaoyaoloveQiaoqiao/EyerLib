//
// Created by chuchun on 2021/2/7.
//

#include "EyerColorSpace.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    EyerColorSpace::EyerColorSpace() {
        EyerLog("EyerColorSpace init=============================\n");
    }

    EyerColorSpace::~EyerColorSpace() {

    }

    int  EyerColorSpace::Convert(){
        EyerLog("EyerColorSpace convert=============================\n");

        return 0;
    }





    Matrix::Matrix()
    {
        rowsize = 3;
        colsize = 3;
        for (int i = 0; i < rowsize; i++)
            for (int j = 0; j < colsize; j++) {
                data[i][j] = (i + j ) * j + 1;
            }
    }

    Matrix::~Matrix()
    {
    }

    void Matrix::initialize()
    {
        using namespace std;
        int myrowsize = 0,	mycolsize = 0;
        cout << "input the size of Matrix (row, col) : " << endl;
        cin >> myrowsize >> mycolsize;
        rowsize = myrowsize;
        colsize = mycolsize;
        cout << "input the value of Matrix !" << endl;
        for (int i = 0; i < myrowsize; i++)
            for (int j = 0; j < mycolsize; j++) {
                cin >> data[i][j];
            }
    }

    void Matrix::show() const
    {
        printf("the rowsize is %d, the colsize is %d\n", rowsize, colsize);
        for (int i = 0; i < rowsize; i++) {
            for (int j = 0; j < colsize; j++)
                printf("%f ", data[i][j]);
            printf("\n");
        }
    }

    int Matrix::get_size() const
    {
        return colsize;
    }

    void Matrix::lupDecomposition(int (*p)[100], double (*left)[100], double (*up)[100])
    {
        int n = get_size();
        int position[100] = {0};

        //初始化position数组
        for (int i = 0; i < n; i++) {
            position[i] = i;
        }

        //定义矩阵a， 并且赋值
        double a[100][100] = {0};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = data[i][j];

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
                    p[i][j] = 1;
                else
                    p[i][j] = 0;
            }

        //给矩阵left赋值
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i == j)
                    left[i][j] = 1;
                else if (i > j)
                    left[i][j] = a[i][j];
                else
                    left[i][j] = 0;
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


    double* Matrix::lupSolve(double (*left)[100], double (*up)[100], int *position, double *b)
    {
        int n = get_size();
        double x[100] = {0};
        double y[100] = {0};

        for (int i = 0; i < n; i++) {
            double partSum = 0;
            for (int j = 0; j <= i-1; j++)
                partSum += left[i][j]*y[j];
            y[i] = b[position[i]] - partSum;
        }

        for (int i = n-1; i >= 0; i--) {
            double partSum = 0;
            for (int j = i+1; j <= n-1; j++)
                partSum += up[i][j] * x[j];
            x[i] = (y[i] - partSum) / up[i][i];
        }
        return x;
    }

    void Matrix::inverse()
    {
        double left[100][100] = {{1, 0, 0}, {0.2, 1, 0}, {0.6, 0.5, 1}};
        double up[100][100] = {{5, 6, 3}, {0, 0.8, -0.6}, {0, 0, 2.5}};
        int position[100] = {2, 0, 1};
        int p[100][100] = {0};

        /*double *x;
        x = lupSolve(left, up, position, b);
        for (int i = 0; i < 3; i++)
            printf("%f ", x[i]);*/

        lupDecomposition(p, left, up);

        //得到position，和得到单位矩阵额e[n][n]
        int n = get_size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (p[i][j] == 1)
                    position[i] = j;
        double e[100][100] = {0};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i == j)
                    e[i][j] = 1;
                else
                    e[i][j] = 0;

        //构造逆矩阵
        double result[100][100] = {0};
        for (int i = 0; i < n; i++) {
            double *x = NULL;
            x = lupSolve(left, up, position, e[i]);
            for (int j = 0; j < n; j++)
                result[j][i] = x[j];
        }

        //打印result数组
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%f ", result[i][j]);
            printf("\n");
        }

        return;
    }

}