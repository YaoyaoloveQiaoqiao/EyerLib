#include <stdio.h>
#include <gtest/gtest.h>

#include "MBGLWindow/MBGLWindow.hpp"
#include "MBGL/MBGL.hpp"
#include "MBGLShader/Shader.hpp"
#include "MBType/MBType.hpp"

/*
TEST(GLWindows, GLWindows){

    MB::MBGLWindow windows("miaowu", 1280, 720);
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
    MB::MBGLVAO vao;
    vao.AddVBO(vertex, sizeof(vertex), 0);
    vao.AddVBO(coor, sizeof(coor), 1);
    vao.SetEBO(index, sizeof(index));

    MB::MBGLDraw draw(MB::GL_SHADER::YUV_VIDEO_VERTEX_SHADER, MB::GL_SHADER::YUV_VIDEO_FRAGMENT_SHADER);
    draw.Init();
    draw.SetVAO(&vao);

    MB::MBType type("./han_yi_xing_kai_jian.ttf");
    int ret = type.Init();
    int indexI = type.GenChar('q', 720);

    MB::MBTypeBitmap b;
    ret = type.GetCharBitmap(indexI, &b);
    if(ret){
        MBLog("GetCharBitmap Error\n");
    }

    MB::MBGLTexture zeroTexture;
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

    MB::MBGLWindow windows("miaowu", width, height);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    MB::MBGLFrameBuffer frameBuffer(width, height);

    MB::MBGLTextDraw textDraw("./xiao_xiao_yuan_pin_ying.ttf");
    textDraw.SetText("Redknot Miaomiao ABC GL gg");
    textDraw.SetColor(0.0, 1.0, 0.0);
    textDraw.SetSize(100);

    textDraw.SetPos(0, 0 + 100);

    // frameBuffer.AddComponent(&textDraw);


    MB::MBGLTextDraw textDraw2("./han_yi_xing_kai_jian.ttf");
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

        MB::MBString timeStr =  MB::MBTime::TimeFormat();
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
