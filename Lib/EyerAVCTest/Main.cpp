#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, AnnexB){

}

TEST(EyerAVC, Decoder)
{
    Eyer::EyerAVCDecoder avcDeocder("./demo_video_176x144_baseline.h264");
    avcDeocder.DecodeAll();
}

TEST(EyerAVC, EyerField){
    Eyer::EyerField fieldA("abc", 12);
    Eyer::EyerField fieldB = fieldA;
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
