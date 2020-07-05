#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerType/EyerType.hpp"
#include "EyerGLWindow/EyerGLWindow.hpp"
#include "EyerGL/EyerGL.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerType/EyerType.hpp"

TEST(EyerType, EyerType){
    Eyer::EyerType type("xiao_xiao_yuan_pin_ying.ttf");
    int ret = type.Init();
    ASSERT_EQ(ret, 0) << "Init Ret Error";

    int index = type.GenChar('0', 200);
    ASSERT_GT(index, 0) << "GenChar Error";
    
    EyerLog("GenChar Index: %d\n", index);

    Eyer::EyerTypeBitmap bitmap;
    ret = type.GetCharBitmap(index, &bitmap);
    ASSERT_EQ(ret, 0) << "GetCharBitmap Ret Error";

    EyerLog("Width: %d\n",bitmap.width);
    EyerLog("Height: %d\n", bitmap.height);
}

TEST(EyerType, EyerTypeMesh){
    Eyer::EyerTypeMesh typeMesh("xiao_xiao_yuan_pin_ying.ttf");
    typeMesh.Gen(L'饕');

    int width = 1280;
    int height = 720;

    Eyer::EyerGLWindow windows("miaowu", width, height);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    Eyer::EyerGLFrameBuffer frameBuffer(width, height);

    while (!windows.ShouldClose()){
        windows.Clear();

        windows.Loop();
    }

    windows.Close();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
