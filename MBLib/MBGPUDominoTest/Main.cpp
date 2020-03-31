#include <stdio.h>
#include <gtest/gtest.h>
#include "MBGPUDomino/MBGPUDomino.hpp"

TEST(GPUDomino, GPUDomino){
    MB::MBGominoGaussianBlur gb;

    MB::MBGominoPip pip;
    pip << &gb;

    // pip.Go()

    pip.PrintStruct();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}