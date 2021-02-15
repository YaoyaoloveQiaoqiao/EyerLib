#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TEST(EyerMath, MatrixInit)
{
    Eyer::EatrixF mat(5, 5);
    mat.PrintInfo();

    Eyer::EatrixF mat2(2, 2);
    mat2.PrintInfo();

    Eyer::EatrixF mat3(1, 1);
    mat3.PrintInfo();

    Eyer::EatrixF mat4(4, 3);
    mat4.PrintInfo();
}

TEST(EyerMath, Matrix4x4)
{
    Eyer::EatrixF4x4 mat4X4;
    mat4X4.PrintInfo();
    Eyer::EatrixF4x4 matA;
    Eyer::EatrixF4x4 matB;
    Eyer::EatrixF4x4 matC = matA * matB;
    matC = matA * matB;
}

bool cmpMat(const Eyer::EatrixF4x4 & matC, const glm::mat4 & testMat)
{
    for(int i=0;i<4;i++){
        Eyer::EyerString str = "";
        for(int j=0;j<4;j++){
            float a = glm::value_ptr(testMat)[i * 4 + j];
            float b = matC.Get(i, j);
            str = str + Eyer::EyerString::Number(a, " %04.4f ");
            str = str + "==";
            str = str + Eyer::EyerString::Number(b, " %04.4f ");
            str = str + "  ";
        }
        EyerLog("%s\n", str.str);
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            float a = glm::value_ptr(testMat)[i * 4 + j];
            float b = matC.Get(i, j);
            if(a != b){
                printf("a: %f, b: %f\n", a, b);
                return false;
            }
        }
    }

    return true;
}

TEST(EyerMath, Matrix4x4_multiplication)
{
    float a[] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
    };
    Eyer::EatrixF4x4 matA;
    matA.SetData(a, 16);

    float b[] = {
            1, 0, 0, 0,
            0, 3, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    };
    Eyer::EatrixF4x4 matB;
    matB.SetData(b, 16);

    EyerLog("==================== * ====================\n");
    Eyer::EatrixF4x4 matC = matA * matB;
    matC.PrintInfo();

    glm::mat4 testMatA = glm::make_mat4(a);
    glm::mat4 testMatB = glm::make_mat4(b);
    glm::mat4 testMatC = testMatB * testMatA;

    ASSERT_EQ(cmpMat(matC, testMatC), true);

    EyerLog("==================== - ====================\n");
    matC = matA - matB;
    matC.PrintInfo();
    testMatC = testMatA - testMatB;

    ASSERT_EQ(cmpMat(matC, testMatC), true);

    EyerLog("==================== + ====================\n");

    matC = matA + matB;
    matC.PrintInfo();
    testMatC = testMatA + testMatB;

    ASSERT_EQ(cmpMat(matC, testMatC), true);
}


TEST(EyerMath, Matrix4x4_perspective)
{

    int width = 1920;
    int height = 1080;

    Eyer::EatrixF4x4 matC;
    matC.SetPerspective(Eyer::Eath::DegreesToRadians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

    cmpMat(~matC, proj);
    // ASSERT_EQ(cmpMat(~matC, proj), true);
}

TEST(EyerMath, Matrix4x4_view)
{
    Eyer::EatrixF4x4 matC;
    matC.LookAt(0.0f, 4.0f, 6.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f
                );

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 4.0f, 6.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    cmpMat(~matC, view);
    // ASSERT_EQ(cmpMat(~matC, proj), true);
}


TEST(EyerMath, ColorSpace)
{
    Eyer::EectorF3 yuv(0.5, 0.0, 0.0);
    float yuv2020_rgb2020[] = {
            1.0000, -0.0000, 1.4746,
            1.0000, -0.1645, -0.5713,
            1.0000, 1.8814, -0.0001
    };
    Eyer::EatrixF3x3 mat_yuv2020_rgb2020;
    mat_yuv2020_rgb2020.SetData(yuv2020_rgb2020, 9);
    mat_yuv2020_rgb2020.PrintInfo();

    Eyer::EectorF3 rgb2020 = mat_yuv2020_rgb2020 * yuv;


    rgb2020.SetX(0.7);
    rgb2020.SetY(0.5);
    rgb2020.SetZ(0.5);
    rgb2020.PrintInfo();



    float rgb2020_xyz[] = {
            0.6370, 0.1446, 0.1689,
            0.2627, 0.6780, 0.0593,
            0,      0.0281, 1.0610
    };
    Eyer::EatrixF3x3 mat_rgb2020_xyz;
    mat_rgb2020_xyz.SetData(rgb2020_xyz, 9);
    mat_rgb2020_xyz.PrintInfo();

    Eyer::EectorF3 xyz = (mat_rgb2020_xyz) * rgb2020;
    xyz.PrintInfo();

    float xyz_rgb709[] = {
            3.240625,	-1.537208,	-0.498629,
            -0.968931,	1.875756,	0.041518,
            0.055710,	-0.204021,	1.056996
    };

    Eyer::EatrixF3x3 mat_xyz_rgb709;
    mat_xyz_rgb709.SetData(xyz_rgb709, 9);
    mat_xyz_rgb709.PrintInfo();

    Eyer::EectorF3 rgb709 = (mat_xyz_rgb709) * xyz;
    rgb709.PrintInfo();



    rgb709 = (mat_xyz_rgb709 * mat_rgb2020_xyz * mat_yuv2020_rgb2020) * yuv;
    rgb709.PrintInfo();

    Eyer::EatrixF3x3 out = mat_xyz_rgb709 * mat_rgb2020_xyz * mat_yuv2020_rgb2020;

    out = ~out;
    out.PrintInfo();
}

TEST(EyerMath, EnterPolation)
{
    Eyer::EectorF3 start(0.0, 0.0, 0.0);
    Eyer::EectorF3 end(1.0, 1.0, 1.0);

    Eyer::EnterPolationF polation(start, end, 0, 1000);

    Eyer::EectorF3 res = polation.Get(600);
    res.PrintInfo();
}

TEST(EyerMath, inverse)
{
    float yuv2020_rgb2020[] = {
            1.0000, -0.0000, 1.4746,
            1.0000, -0.1645, -0.5713,
            1.0000, 1.8814, -0.0001
    };

    float rgb2020_xyz[] = {
            0.6370, 0.1446, 0.1689,
            0.2627, 0.6780, 0.0593,
            0,      0.0281, 1.0610
    };

    float rgb709_xyz[] = {
            0.4124, 0.3576, 0.1805,
            0.2126, 0.7152, 0.0722,
            0.0193, 0.1192, 0.9505
    };

    Eyer::Eatrix<float> mat(3, 3);
    mat.SetData(rgb709_xyz, 9);


    Eyer::Eatrix<float> inv_mat = !mat;
    inv_mat.PrintInfo();

    Eyer::Eatrix<float> multiple_mat = mat * inv_mat;
    multiple_mat.PrintInfo();


}

int main(int argc,char **argv){
    eyer_log_thread(0);

    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}