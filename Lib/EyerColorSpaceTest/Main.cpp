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

void out(Eyer::EatrixF3x3 mat, const char* s)
{
    cout << s << endl;
    for (int i = 0; i < 3; i++) {
        Eyer::EyerString str = "";
        for (int j = 0; j < 3; j++){
            str = str + Eyer::EyerString::Number(mat.Get(i, j), " %.4f ");
        }
        EyerLog("%s\n", str.str);
    }
    cout << endl;
}

void product(Eyer::EatrixF3x3 a, Eyer::EatrixF3x3 b, Eyer::EatrixF3x3 matrix_result)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++){
                float tmp = matrix_result.Get(i, j) + (a.Get(i, k) * b.Get(k, j));
                matrix_result.Set(i, j, tmp);
            }
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

    void out(Eyer::EatrixF3x3 a, const char* s);
    void product(Eyer::EatrixF3x3 a, Eyer::EatrixF3x3 b, Eyer::EatrixF3x3 matrix_result);

    //初始化
    Eyer::EatrixF3x3 l;
    Eyer::EatrixF3x3 u;
    Eyer::EatrixF3x3 c;
    Eyer::EatrixF3x3 ad_l;
    Eyer::EatrixF3x3 ad_u;

    //LU分解
    for (int i = 0; i < n; i++)
        l.Set(i, i, 1);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n; j++)
        {
            float tem = 0;
            for (int k = 0; k < i; k++)
                tem += l.Get(i, k) * u.Get(k, j);
            u.Set(i, j, a.Get(i, j) - tem);
        }
        for (int j = i + 1; j < n; j++)
        {
            float tem = 0;
            for (int k = 0; k < i; k++)
                tem += l.Get(j, k) * u.Get(k, i);
            l.Set(j, i, (a.Get(j, i) - tem) / u.Get(i, i));
        }
    }
    u.Set(n - 1, n - 1, a.Get(n-1, n-1));
    for (int i = 0; i < n - 1; i++){
        float tem = u.Get(n - 1, n - 1) - (l.Get(n - 1, i) * u.Get(i, n - 1));
        u.Set(n - 1, n - 1, tem);
    }

    //U的逆矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j) ad_u.Set(i, j, 0);
            else if (i == j)
            {
                ad_u.Set(i, j, 1);
                for (int k = 0; k < n; k++)
                    if (k != j){
                        float tem = ad_u.Get(i, j) * u.Get(k, k);
                        ad_u.Set(i, j, tem);
                    }
            }
            else if (j - i == 1)
            {
                float tem = ad_u.Get(i, j) - u.Get(i, j);
                ad_u.Set(i, j, tem);
                for (int k = 0; k < n; k++)
                    if (k != i && k != j){
                        float tem = ad_u.Get(i, j) * u.Get(k, k);
                        ad_u.Set(i, j, tem);
                    }
            }
            else if (j - i >= 2)
            {
                float deltas_aii = 1;
                for (int k = 0; k < n; k++)
                    if (k < i || k > j)
                        deltas_aii *= u.Get(k, k);
                int permutation[n];
                for (int t = 0; t < j - i; t++) permutation[t] = i + t + 1;
                float sum = 0;
                do
                {
                    int cnt = 0;
                    for (int t2 = 0; t2 < j - i; t2++)
                        for (int t3 = t2; t3 < j - i; t3++)
                            if (permutation[t3] < permutation[t2]) cnt++;
                    float mul = 1;
                    for (int t1 = i; t1 < j; t1++)
                        mul *= u.Get(t1, permutation[t1 - i]);
                    if ((j - i + 1) % 2 == 0)mul *= -1;
                    if (cnt % 2 == 0) sum += mul;
                    else sum -= mul;
                } while (next_permutation(permutation, permutation + j - i));
                ad_u.Set(i, j, sum * deltas_aii);
            }
        }
    }
    float det_u = 1;
    for (int k = 0; k < n; k++) det_u *= u.Get(k, k);
    if (det_u < 1e-16)
    {
        printf("矩阵不可逆，请检查输入！\n");
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            float tem = ad_u.Get(i, j) / det_u;
            ad_u.Set(i, j, tem);
        }


    //l的逆矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < j) ad_l.Set(i, j, 0);
            else if (i == j)
            {
                ad_l.Set(i, j, 1);
                for (int k = 0; k < n; k++)
                    if (k != j){
                        float tem = ad_l.Get(i, j) * l.Get(k, k);
                        ad_l.Set(i, j, tem);
                    }
            }
            else if (i - j == 1)
            {
                ad_l.Set(i, j, -l.Get(i, j));
                for (int k = 0; k < n; k++)
                    if (k != i && k != j){
                        float tem = ad_l.Get(i, j) * l.Get(k, k);
                        ad_l.Set(i, j, tem);
                    }
            }
            else if (i - j >= 2)
            {
                float deltas_aii = 1;
                for (int k = 0; k < n; k++)
                    if (k < i || k > j)
                        deltas_aii *= l.Get(i, i);
                int permutation[n];
                for (int t = 0; t < i - j; t++) permutation[t] = j + t + 1;
                float sum = 0;
                do
                {
                    int cnt = 0;
                    for (int t2 = 0; t2 < i - j; t2++)
                        for (int t3 = t2; t3 < i - j; t3++)
                            if (permutation[t3] < permutation[t2]) cnt++;
                    float mul = 1;
                    for (int t1 = j; t1 < i; t1++)
                        mul *= l.Get(permutation[t1 - j], t1);
                    if ((i - j + 1) % 2 == 0)mul *= -1;
                    if (cnt % 2 == 0) sum += mul;
                    else sum -= mul;
                } while (next_permutation(permutation, permutation + i - j));
                ad_l.Set(i, j, sum * deltas_aii);
            }
        }
    }
    float det_l = 1;
    for (int k = 0; k < n; k++) det_l *= l.Get(k, k);
    if (det_u < 1e-16)
    {
        printf("矩阵不可逆，请检查输入！\n");
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            float tem = ad_l.Get(i, j) / det_l;
            ad_l.Set(i, j, tem);
        }
    //矩阵inv_L
    //out(ad_l, "矩阵inv_L=");
    //L*L-1
    //memset(c, 0, n*n * sizeof(float));
    //product(l, ad_l, c);
    //out(c, "矩阵L*inv_L=");


    //矩阵a
    //out(a, "矩阵a=");
    EyerLog("矩阵a:\n");
    a.PrintInfo();
    //inv_a
    product(ad_u, ad_l, inv_a);
    out(inv_a, "逆矩阵inv_a=");
    //EyerLog("逆矩阵inv_a:\n");
    //inv_a.PrintInfo();

    //验证a*inv_a
//    product(a, inv_a, c);
//    EyerLog("矩阵a*inv_a:\n");
//    c.PrintInfo();


    //mat_xyz_rgb709.PrintInfo();
    /*double *A = new double[N*N]();

    srand((unsigned)time(0));
    for(int i=0; i<N ;i++)
    {
        for(int j=0; j<N;j++)
        {
            A[i*N+j]=rand()%100 *0.01;
        }
    }


    double *E_test = new double[N*N]();
    double *invOfA = new double[N*N]();
    invOfA=LUP_solve_inverse(A);

    E_test=mul(A,invOfA);    //验证精确度

    cout<< "矩阵A:" <<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<< A[i*N+j]<< " " ;
        }
        cout<<endl;
    }

    cout<< "inv_A:" <<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<< invOfA[i*N+j]<< " " ;
        }
        cout<<endl;
    }

    cout<< "E_test:" <<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<< E_test[i*N+j]<< " " ;
        }
        cout<<endl;
    }*/
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}