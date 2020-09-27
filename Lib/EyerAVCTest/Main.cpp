#include <gtest/gtest.h>
#include <EyerAVC/EyerSPS.hpp>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, AnnexB){
    // Eyer::EyerString url = "C:/Video/video.h264";
    // Eyer::EyerString url = "/Users/lichi/annie/xinxiaomen.h264";
    Eyer::EyerString url = "/Users/lichi/annie/xinxiaomen.h264";

    Eyer::EyerAnnexB annexB;
    annexB.Open(url);

    while(1){
        Eyer::EyerNALU nalu(8 * 1024 * 1024);
        int ret = annexB.GetAnnexBNALU(nalu);
        // EyerLog("nalu len: %d, nalu type: %d, nalu startcodelen: %d\n", nalu.len, nalu.nal_unit_type, nalu.startcodeprefix_len);
        if(ret <= 0){
            break;
        }

        int len = nalu.len;
        nalu.ToRBSP();

        if(len != nalu.len){
            // EyerLog("nalu len: %d, nalu type: %d, nalu startcodelen: %d\n", nalu.len, nalu.nal_unit_type, nalu.startcodeprefix_len);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SPS){
            EyerLog("SPS\n");
            Eyer::EyerSPS sps(nalu);
            sps.PrintInfo();
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_PPS){
            EyerLog("PPS\n");
        }
    }

    annexB.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
