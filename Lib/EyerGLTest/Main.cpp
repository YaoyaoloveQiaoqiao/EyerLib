#include <stdio.h>
#include <gtest/gtest.h>

#include "EyerGLWindow/EyerGLWindow.hpp"
#include "EyerGL/EyerGL.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerType/EyerType.hpp"
#include "EyerGLContext/EyerGLContext.hpp"

TEST(GLContext, GLContextTest){
    Eyer::EyerGLContextThread glCtx;
    glCtx.Start();

    for(int i=0;i<100;i++){
        Eyer::EyerTime::EyerSleep(1000 * 1000);
    }

    glCtx.Stop();
}

/*
TEST(GLWindows, GLWindows){

    Eyer::EyerGLWindow windows("miaowu", 1280, 720);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    float vertex[] = {
            1.0, 1.0, 0.0,
            1.0, -1.0, 0.0,
            -1.0, -1.0, 0.0,
            -1.0, 1.0, 0.0
    };
    float coor[] = {
            1.0, 1.0, 0.0,
            1.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
    };
    unsigned int index[] = {
            0, 1, 2,
            0, 2, 3
    };
    Eyer::EyerGLVAO vao;
    vao.AddVBO(vertex, sizeof(vertex), 0);
    vao.AddVBO(coor, sizeof(coor), 1);
    vao.SetEBO(index, sizeof(index));

    Eyer::EyerGLDraw draw(Eyer::GL_SHADER::YUV_VIDEO_VERTEX_SHADER, Eyer::GL_SHADER::YUV_VIDEO_FRAGMENT_SHADER);
    draw.Init();
    draw.SetVAO(&vao);

    Eyer::EyerType type("./han_yi_xing_kai_jian.ttf");
    int ret = type.Init();
    int indexI = type.GenChar('q', 720);

    Eyer::EyerTypeBitmap b;
    ret = type.GetCharBitmap(indexI, &b);
    if(ret){
        EyerLog("GetCharBitmap Error\n");
    }

    Eyer::EyerGLTexture zeroTexture;
    zeroTexture.SetDataRedChannel(b.data, b.width, b.height);

    draw.PutTexture("numberTex", &zeroTexture);

    while (!windows.ShouldClose()){
        windows.Clear();

        draw.Draw();

        windows.Loop();
    }

    windows.Close();
}

TEST(GLWindows, GLWindowsText){

    int width = 1280;
    int height = 720;

    Eyer::EyerGLWindow windows("miaowu", width, height);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    Eyer::EyerGLFrameBuffer frameBuffer(width, height);

    Eyer::EyerGLTextDraw textDraw("./xiao_xiao_yuan_pin_ying.ttf");
    textDraw.SetText("Redknot Miaomiao ABC GL gg");
    textDraw.SetColor(0.0, 1.0, 0.0);
    textDraw.SetSize(100);

    textDraw.SetPos(0, 0 + 100);

    // frameBuffer.AddComponent(&textDraw);


    Eyer::EyerGLTextDraw textDraw2("./han_yi_xing_kai_jian.ttf");
    textDraw2.SetText("大学之道，在明明德。");
    textDraw2.SetColor(0.0, 0.0, 0.0);
    textDraw2.SetSize(100);

    textDraw2.SetPos(0, 0 + 300);

    // frameBuffer.AddComponent(&textDraw2);

    while (!windows.ShouldClose()){
        windows.Clear();

        frameBuffer.AddComponent(&textDraw);
        frameBuffer.AddComponent(&textDraw2);

        int textWidth = textDraw2.GetTextWidth();
        textDraw2.SetPos((width - textWidth) / 2 , 0 + 300);

        Eyer::EyerString timeStr =  Eyer::EyerTime::TimeFormat();
        textDraw.SetText(timeStr);
        textDraw.SetPos(0, 0 + 100);
        textDraw.SetColor(1.0, 0.0, 0.0);
        textDraw.Viewport(width, height);
        textDraw2.Viewport(width, height);

        frameBuffer.Draw();
        frameBuffer.ClearAllComponent();

        windows.Loop();
    }

    windows.Close();

}
*/

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
