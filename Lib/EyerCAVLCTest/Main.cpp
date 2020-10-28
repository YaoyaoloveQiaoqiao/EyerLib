#include <gtest/gtest.h>
#include "EyerCAVLC/EyerCAVLC.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(EyerCAVLC, EyerCAVLCTest)
{
    Eyer::CAVLC cavlc;
    cavlc.Encode();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
