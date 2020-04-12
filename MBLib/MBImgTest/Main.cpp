#include <stdio.h>
#include <gtest/gtest.h>

#define STB_IMAGE_IMPLEMENTATION
#include "MBImg/stb_image.h"
#include "MBCore/MBCore.hpp"

TEST(MB, MBImg){
    int width, height, nrChannels;
    unsigned char * data = stbi_load("1.jpg", &width, &height, &nrChannels, 0);
    printf("width:%d height:%d\n",width, height);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}