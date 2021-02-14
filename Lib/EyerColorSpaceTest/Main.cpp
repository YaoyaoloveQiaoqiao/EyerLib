#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

#include "EyerColorSpace/EyerColorSpace.hpp"

#include <iostream>
#include <cmath>
#include <ctime>

#define N 3
using namespace std;

//矩阵乘法
double * mul(double A[N*N],double B[N*N])
{
    double *C=new double[N*N]{};
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            for(int k=0;k<N;k++)
            {
                C[i*N+j] += A[i*N+k]*B[k*N+j];
            }
        }
    }

    //若绝对值小于10^-10,则置为0（这是我自己定的）
    for(int i=0;i<N*N;i++)
    {
        if(abs(C[i])<pow(10,-10))
        {
            C[i]=0;
        }
    }

    return C;
}

//LUP分解
void LUP_Descomposition(double A[N*N],double L[N*N],double U[N*N],int P[N])
{
    int row=0;
    for(int i=0;i<N;i++)
    {
        P[i]=i;
    }
    for(int i=0;i<N-1;i++)
    {
        double p=0.0;
        for(int j=i;j<N;j++)
        {
            if(abs(A[j*N+i])>p)
            {
                p=abs(A[j*N+i]);
                row=j;
            }
        }
        if(0==p)
        {
            cout<< "矩阵奇异，无法计算逆" <<endl;
            return ;
        }

        //交换P[i]和P[row]
        int tmp=P[i];
        P[i]=P[row];
        P[row]=tmp;

        double tmp2=0.0;
        for(int j=0;j<N;j++)
        {
            //交换A[i][j]和 A[row][j]
            tmp2=A[i*N+j];
            A[i*N+j]=A[row*N+j];
            A[row*N+j]=tmp2;
        }

        //以下同LU分解
        double u=A[i*N+i],l=0.0;
        for(int j=i+1;j<N;j++)
        {
            l=A[j*N+i]/u;
            A[j*N+i]=l;
            for(int k=i+1;k<N;k++)
            {
                A[j*N+k]=A[j*N+k]-A[i*N+k]*l;
            }
        }

    }

    //构造L和U
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(i!=j)
            {
                L[i*N+j]=A[i*N+j];
            }
            else
            {
                L[i*N+j]=1;
            }
        }
        for(int k=i;k<N;k++)
        {
            U[i*N+k]=A[i*N+k];
        }
    }

}

//LUP求解方程
double * LUP_Solve(double L[N*N],double U[N*N],int P[N],double b[N])
{
    double *x=new double[N]();
    double *y=new double[N]();

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

/*****************矩阵原地转置BEGIN********************/

/* 后继 */
int getNext(int i, int m, int n)
{
    return (i%n)*m + i/n;
}

/* 前驱 */
int getPre(int i, int m, int n)
{
    return (i%m)*n + i/m;
}

/* 处理以下标i为起点的环 */
void movedata(double *mtx, int i, int m, int n)
{
    double temp = mtx[i]; // 暂存
    int cur = i;    // 当前下标
    int pre = getPre(cur, m, n);
    while(pre != i)
    {
        mtx[cur] = mtx[pre];
        cur = pre;
        pre = getPre(cur, m, n);
    }
    mtx[cur] = temp;
}

/* 转置，即循环处理所有环 */
void transpose(double *mtx, int m, int n)
{
    for(int i=0; i<m*n; ++i)
    {
        int next = getNext(i, m, n);
        while(next > i) // 若存在后继小于i说明重复,就不进行下去了（只有不重复时进入while循环）
            next = getNext(next, m, n);
        if(next == i)  // 处理当前环
            movedata(mtx, i, m, n);
    }
}
/*****************矩阵原地转置END********************/

//LUP求逆(将每列b求出的各列x进行组装)
double * LUP_solve_inverse(double A[N*N])
{
    //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
    double *A_mirror = new double[N*N]();
    double *inv_A=new double[N*N]();//最终的逆矩阵（还需要转置）
    double *inv_A_each=new double[N]();//矩阵逆的各列
    //double *B    =new double[N*N]();
    double *b    =new double[N]();//b阵为B阵的列矩阵分量

    for(int i=0;i<N;i++)
    {
        double *L=new double[N*N]();
        double *U=new double[N*N]();
        int *P=new int[N]();

        //构造单位阵的每一列
        for(int i=0;i<N;i++)
        {
            b[i]=0;
        }
        b[i]=1;

        //每次都需要重新将A复制一份
        for(int i=0;i<N*N;i++)
        {
            A_mirror[i]=A[i];
        }

        LUP_Descomposition(A_mirror,L,U,P);

        inv_A_each=LUP_Solve (L,U,P,b);
        memcpy(inv_A+i*N,inv_A_each,N*sizeof(double));//将各列拼接起来
    }
    transpose(inv_A,N,N);//由于现在根据每列b算出的x按行存储，因此需转置

    return inv_A;
}

const int n=3;//逆矩阵阶数，求不同阶数矩阵请修改n的值

/*void out(double matrix[][n], const char* s)
{
    cout << s << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fabs(*(*(matrix + i) + j))<1e-10? cout << 0 << '\t':cout << *(*(matrix + i) + j) << '\t';
        cout << endl;
    }
    cout << endl;
}*/

void out(    Eyer::EatrixF3x3 matrix, const char* s)
{
    cout << s << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            cout << matrix.Get(i, j) << '\t';
        }
            //fabs(*(*(matrix + i) + j))<1e-10? cout << 0 << '\t':cout << *(*(matrix + i) + j) << '\t';
        cout << endl;
    }
    cout << endl;
}

void out(    double matrix1[n][n], const char* s)
{
    cout << s << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            cout << matrix1[i][j] << '\t';
        }
        //fabs(*(*(matrix + i) + j))<1e-10? cout << 0 << '\t':cout << *(*(matrix + i) + j) << '\t';
        cout << endl;
    }
    cout << endl;
}

void product(double matrix1[n][n], double matrix2[n][n], Eyer::EatrixF3x3 & matrix_result)
{
    out(matrix1, "matrix1:");
    out(matrix2, "matrix2:");

    for (int i = 0; i < matrix_result.row; i++) {
        for (int j = 0; j < matrix_result.col; j++) {
            matrix_result.mat[i][j] = 0.0f;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++){
                double tmp = matrix_result.Get(i, j) + matrix1[i][k] * matrix2[k][j];
                matrix_result.Set(i, j, tmp);
                //matrix_result[i][j] = tmp;
            }

                //matrix_result.Set(i, j, matrix_result.Get(i, j) + matrix1[i][k] * matrix2[k][j]);


}

TEST(EyerColorSpace, init)
{
    float yuv2020_rgb2020[] = {
            1.0000, -0.0000, 1.4746,
            1.0000, -0.1645, -0.5713,
            1.0000, 1.8814, -0.0001
    };
    Eyer::EatrixF3x3 a;
    a.SetData(yuv2020_rgb2020, 9);

    Eyer::EatrixF3x3 inv_a;
    //double inv_a[n][n];
    //memset(inv_a, 0, n * n * sizeof(double));

    //初始化
    double l[n][n], u[n][n], c[n][n], ad_l[n][n], ad_u[n][n];
    memset(l, 0, n * n * sizeof(double));
    memset(u, 0, n * n * sizeof(double));
    memset(c, 0, n * n * sizeof(double));
    memset(ad_l, 0, n * n * sizeof(double));
    memset(ad_u, 0, n * n * sizeof(double));


    //LU分解
    for (int i = 0; i < n; i++)
        l[i][i] = 1;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n; j++)
        {
            double tem = 0;
            for (int k = 0; k < i; k++)
                tem += l[i][k] * u[k][j];
            u[i][j] = a.Get(i, j) - tem;
        }
        for (int j = i + 1; j < n; j++)
        {
            double tem = 0;
            for (int k = 0; k < i; k++)
                tem += l[j][k] * u[k][i];
            l[j][i] = (a.Get(j, i) - tem) / u[i][i];
        }
    }
    u[n - 1][n - 1] = a.Get(n - 1, n - 1);
    for (int i = 0; i < n - 1; i++)
        u[n - 1][n - 1] -= l[n - 1][i] * u[i][n - 1];
    //矩阵L
    //out(l, "矩阵L");
    //矩阵U
    //out(u, "矩阵U");
    //L*U
    //product(l,u, c);
    //out(c, "矩阵L*U");


    //U的逆矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j) ad_u[i][j] = 0;
            else if (i == j)
            {
                ad_u[i][j] = 1;
                for (int k = 0; k < n; k++)
                    if (k != j)
                        ad_u[i][j] *= u[k][k];
            }
            else if (j - i == 1)
            {
                ad_u[i][j] = -u[i][j];
                for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        ad_u[i][j] *= u[k][k];
            }
            else if (j - i >= 2)
            {
                double deltas_aii = 1;
                for (int k = 0; k < n; k++)
                    if (k < i || k > j)
                        deltas_aii *= u[k][k];
                int permutation[n];
                for (int t = 0; t < j - i; t++) permutation[t] = i + t + 1;
                double sum = 0;
                do
                {
                    int cnt = 0;
                    for (int t2 = 0; t2 < j - i; t2++)
                        for (int t3 = t2; t3 < j - i; t3++)
                            if (permutation[t3] < permutation[t2]) cnt++;
                    double mul = 1;
                    for (int t1 = i; t1 < j; t1++)
                        mul *= u[t1][permutation[t1 - i]];
                    if ((j - i + 1) % 2 == 0)mul *= -1;
                    if (cnt % 2 == 0) sum += mul;
                    else sum -= mul;
                } while (next_permutation(permutation, permutation + j - i));
                ad_u[i][j] = sum * deltas_aii;
            }
        }
    }
    double det_u = 1;
    for (int k = 0; k < n; k++) det_u *= u[k][k];
    if (det_u < 1e-16)
    {
        printf("矩阵不可逆，请检查输入！\n");
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ad_u[i][j] /= det_u;
    //inv_U
    //out(ad_u, "inv_U");
    //U*U-1
    //memset(c, 0, n*n * sizeof(double));
    //product(u, ad_u, c);
    //out(c, "矩阵U*U-1");


    //l的逆矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < j) ad_l[i][j] = 0;
            else if (i == j)
            {
                ad_l[i][j] = 1;
                for (int k = 0; k < n; k++)
                    if (k != j)
                        ad_l[i][j] *= l[k][k];
            }
            else if (i - j == 1)
            {
                ad_l[i][j] = -l[i][j];
                for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        ad_l[i][j] *= l[k][k];
            }
            else if (i - j >= 2)
            {
                double deltas_aii = 1;
                for (int k = 0; k < n; k++)
                    if (k < i || k > j)
                        deltas_aii *= l[i][i];
                int permutation[n];
                for (int t = 0; t < i - j; t++) permutation[t] = j + t + 1;
                double sum = 0;
                do
                {
                    int cnt = 0;
                    for (int t2 = 0; t2 < i - j; t2++)
                        for (int t3 = t2; t3 < i - j; t3++)
                            if (permutation[t3] < permutation[t2]) cnt++;
                    double mul = 1;
                    for (int t1 = j; t1 < i; t1++)
                        mul *= l[permutation[t1 - j]][t1];
                    if ((i - j + 1) % 2 == 0)mul *= -1;
                    if (cnt % 2 == 0) sum += mul;
                    else sum -= mul;
                } while (next_permutation(permutation, permutation + i - j));
                ad_l[i][j] = sum * deltas_aii;
            }
        }
    }
    double det_l = 1;
    for (int k = 0; k < n; k++) det_l *= l[k][k];
    if (det_u < 1e-16)
    {
        printf("矩阵不可逆，请检查输入！\n");
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ad_l[i][j] /= det_l;
    //矩阵inv_L
    //out(ad_l, "矩阵inv_L=");
    //L*L-1
    //memset(c, 0, n*n * sizeof(double));
    //product(l, ad_l, c);
    //out(c, "矩阵L*inv_L=");


    //矩阵a
    //out(a, "矩阵a=");
    //EyerLog("矩阵a=\n");
    //a.PrintInfo();
    //inv_a
    product(ad_u, ad_l, inv_a);
    out(inv_a, "逆矩阵inv_a=");
    //EyerLog("逆矩阵inv_a=\n");
    //inv_a.PrintInfo();

    //验证a*inv_a
    //memset(c, 0, n * n * sizeof(double));
    //product(a, inv_a, c);

    //out(c, "矩阵a*inv_a=");
   //EyerLog("矩阵a*inv_a=\n");
    //(a * inv_a).PrintInfo();


}


int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}