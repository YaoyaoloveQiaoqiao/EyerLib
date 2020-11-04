#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"

#include "EyerGLWindow/EyerGLWindow.hpp"
#include "EyerGL/EyerGL.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerType/EyerType.hpp"
#include "EyerGLContext/EyerGLContext.hpp"

TEST(GLWindows, GLWindows)
{
    Eyer::EyerGLWindow windows("miaowu", 1280, 720);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    Eyer::EyerGLJulia julia;
    julia.SetWH(1280, 720);
    while (!windows.ShouldClose()){
        windows.Clear();

        julia.Draw();
        Eyer::EyerTime::EyerSleepMilliseconds(10);

        windows.Loop();
    }

    windows.Close();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
