#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerSignal/EyerSignal.hpp"

TEST(EyerSignal, EyerSignalTest)
{

}

TEST(EyerSignal, DCT)
{
    int len = 128;
    float input[len];
    for(int i = 0;i<len;i++){
        input[i] = sin(i * 1.0f) * 0.5f + 0.5f;
        // EyerLog("%f\n", input[i]);
    }

    Eyer::DCT<float> dct;

    float output[len];
    dct.DCT1D(input, len, output, len);

    for(int i = 0;i<len;i++){
        EyerLog("%f\n", output[i]);
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
