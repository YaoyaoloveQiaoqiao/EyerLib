#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerGPUDomino/EyerGPUDomino.hpp"

TEST(GPUDomino, GPUDomino){
    Eyer::EyerGominoSoulout gb;

    Eyer::EyerGominoPip pip;
    pip << &gb;

    //pip.Go();

    pip.PrintStruct();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}