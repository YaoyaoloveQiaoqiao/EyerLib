#ifndef EYERLIB_NALUREADER_HPP
#define EYERLIB_NALUREADER_HPP

#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, NALUReader)
{
    // Eyer::EyerAnnexB annexB("./demo_video_176x144_baseline.h264");
    Eyer::EyerAnnexB annexB("./demo_video.h264");

    while(1){
        Eyer::EyerNALUData nalu;
        int ret = annexB.ReadNALU(nalu);
        if(ret){
            break;
        }

        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_SPS){
            Eyer::EyerSPS sps;
            sps.SetNALUData(nalu);
            sps.Parse();
            sps.PrintInfo();
        }
        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_PPS){
            Eyer::EyerPPS pps;
            pps.SetNALUData(nalu);
            pps.Parse();
            pps.PrintInfo();
        }
    }
}

#endif //EYERLIB_NALUREADER_HPP
