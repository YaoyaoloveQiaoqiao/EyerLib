#include <stdio.h>
#include <gtest/gtest.h>

#include "EyerImg/EyerImg.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(Eyer, EyerImg){
    Eyer::EyerImg img((char *)"1.jpg");
    img.LoadImg();
    printf("width:%d height:%d\n",img.GetImgW(), img.GetImgH());
    unsigned char * _imgData = (unsigned char *)malloc(img.GetImgW() * img.GetImgH() * img.GetImgChannel());
    img.GetImgData(_imgData);
    img.WriteJPG("out.jpg", img.GetImgW(), img.GetImgH(), img.GetImgChannel(), _imgData,0);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}