#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerSignal/EyerSignal.hpp"

TEST(EyerSignal, EyerSignalTest)
{

}

TEST(EyerSignal, DCT)
{
    float input[1024];
    for(int i = 0;i<1024;i++){
        input[i] = sin(i * 1.0f);
        EyerLog("%f\n", input[i]);
    }

    Eyer::DCT<float> dct;

    float output[1024];
    dct.DCT1D(input, 1024, output, 1024);

    for(int i = 0;i<1024;i++){
        EyerLog("%f\n", output[i]);
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
