#include <gtest/gtest.h>
#include "MBRender/MBRender.hpp"

TEST(TGAFile, createFile){
    MB::MBTGAColor white = MB::MBTGAColor(255, 255, 255, 255);
    MB::MBTGAColor red   = MB::MBTGAColor(255, 0,   0,   255);

    MB::MBTgaImage image(100, 100, MB::MBTgaImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically();
	image.write_tga_file("TGAFile_CreateFileTest.tga");
}

TEST(TGAFile, Canvas){
    int width = 1920;
    int height = 1080;

    MB::MBCanvas canvas(width, height);

    for(int i=0;i<5;i++) {
        int x1 = MB::MBRand::Rand(width);
        int y1 = MB::MBRand::Rand(height);
        int x2 = MB::MBRand::Rand(width);
        int y2 = MB::MBRand::Rand(height);

        unsigned char r = MB::MBRand::Rand(255);
        unsigned char g = MB::MBRand::Rand(255);
        unsigned char b = MB::MBRand::Rand(255);

        canvas.DrawLine(x1, y1, x2, y2, r, g, b);
    }

    for(int i=0;i<5;i++) {
        int x0 = MB::MBRand::Rand(width);
        int y0 = MB::MBRand::Rand(height);
        MB::MBVec2 p0(x0, y0);

        int x1 = MB::MBRand::Rand(width);
        int y1 = MB::MBRand::Rand(height);
        MB::MBVec2 p1(x1, y1);

        int x2 = MB::MBRand::Rand(width);
        int y2 = MB::MBRand::Rand(height);
        MB::MBVec2 p2(x2, y2);

        canvas.DrawTriangle(p0, p1, p2);
    }
    
    canvas.RenderToTGA("TGAFile_CanvasTest.tga");
}


TEST(TGAFile, ReadModel_DrawLine){
    int width = 800;
    int height = 800;

    MB::MBCanvas canvas(width, height);

    MB::MBObjModel model("african_head.obj");
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j=0; j<3; j++) {
            MB::MBVec3 v0 = model.vert(face[j]);
            MB::MBVec3 v1 = model.vert(face[(j+1)%3]);
            int x0 = (v0.x()+1.)*width/2.;
            int y0 = (v0.y()+1.)*height/2.;
            int x1 = (v1.x()+1.)*width/2.;
            int y1 = (v1.y()+1.)*height/2.;

            canvas.DrawLine(x0, y0, x1, y1, 0, 0, 0);
        }
    }

    canvas.RenderToTGA("TGAFile_ReadObjModel.tga");
}



TEST(TGAFile, Filling_triangles){
    int width = 2000;
    int height = 2000;

    MB::MBCanvas canvas(width, height);

    {
        MB::MBVec2 triang0_p0(100, 700);
        MB::MBVec2 triang0_p1(500, 1600);
        MB::MBVec2 triang0_p2(700, 800);
        canvas.DrawTriangle(triang0_p0, triang0_p1, triang0_p2);
    }
    {
        MB::MBVec2 triang0_p0(1800, 500);
        MB::MBVec2 triang0_p1(1500, 10);
        MB::MBVec2 triang0_p2(700, 1800);
        canvas.DrawTriangle(triang0_p0, triang0_p1, triang0_p2);
    }
    {
        MB::MBVec2 triang0_p0(1800, 1500);
        MB::MBVec2 triang0_p1(1200, 1600);
        MB::MBVec2 triang0_p2(1300, 1800);
        canvas.DrawTriangle(triang0_p0, triang0_p1, triang0_p2);
    }

    canvas.RenderToTGA("TGAFile_Filling_triangles.tga");
}



TEST(TGAFile, ReadModel_DrawModelFill){
    int width = 2000;
    int height = 2000;

    MB::MBCanvas canvas(width, height);

    MB::MBObjModel model("african_head.obj");
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        MB::MBVec3 p0_3v = model.vert(face[0]);
        MB::MBVec3 p1_3v = model.vert(face[1]);
        MB::MBVec3 p2_3v = model.vert(face[2]);

        MB::MBVec2 p0((p0_3v.x() + 1.0f) * width / 2.0f, (p0_3v.y() + 1.0f) * height / 2.0f);
        MB::MBVec2 p1((p1_3v.x() + 1.0f) * width / 2.0f, (p1_3v.y() + 1.0f) * height / 2.0f);
        MB::MBVec2 p2((p2_3v.x() + 1.0f) * width / 2.0f, (p2_3v.y() + 1.0f) * height / 2.0f);

        unsigned char r = MB::MBRand::Rand(255);
        unsigned char g = MB::MBRand::Rand(255);
        unsigned char b = MB::MBRand::Rand(255);

        canvas.DrawTriangle(p0, p1, p2, r, g, b);
    }

    canvas.RenderToTGA("TGAFile_ReadObjModel_DrawModelFill.tga");
}



TEST(TGAFile, Texture){
    int width = 2000;
    int height = 2000;

    MB::MBCanvas canvas(width, height);

    {
        MB::MBVertex v0(-1.0f, 1.0f, 0.0f, 0.0, 1.0, 0.0);
        MB::MBVertex v1(1.0f, 1.0f, 0.0f, 1.0, 1.0, 0.0);
        MB::MBVertex v2(-1.0f, -1.0f, 0.0f, 0.0, 0.0, 0.0);
        canvas.DrawTriangle(v0, v1, v2);
    }

    canvas.RenderToTGA("TGAFile_Texture.tga");
}