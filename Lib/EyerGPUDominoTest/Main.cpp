#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerGPUDomino/EyerGPUDomino.hpp"

TEST(GPUDomino, GPUDomino){
    Eyer::EyerGominoSoulout gb1;
    Eyer::EyerGominoSoulout gb2;
    Eyer::EyerGominoSoulout gb3;
    Eyer::EyerGominoSoulout gb4;
    Eyer::EyerGominoSoulout gb5;
    Eyer::EyerGominoSoulout gb6;
    Eyer::EyerGominoSoulout gb7;

    Eyer::EyerGominoPip pip;


    gb1 << gb2 << gb3 << gb4 << gb5 << gb6 << gb7;

    // pip.Go();

    pip.PrintStruct();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}