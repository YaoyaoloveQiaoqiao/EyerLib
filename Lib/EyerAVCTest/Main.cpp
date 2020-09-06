#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, AnnexB){
    Eyer::EyerString url = "C:/Video/video.h264";

    Eyer::EyerAnnexB annexB;
    annexB.Open(url);

    annexB.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}