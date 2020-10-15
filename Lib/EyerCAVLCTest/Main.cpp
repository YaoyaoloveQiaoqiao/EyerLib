#include <gtest/gtest.h>
#include "EyerCAVLC/EyerCAVLC.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(EyerCAVLC, EyerCAVLCTest)
{
    int coeff[16] = {
            3, 2, 1, -1, 0, -1,0, 1, 0, 0, 0, 0, 0, 0, 0, 0
    };

    Eyer::CAVLC cavlc;
    std::string res = cavlc.Encoding_cavlc_16x16(coeff);

    EyerLog("Encoding_cavlc_16x16: %s\n", res.c_str());
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
