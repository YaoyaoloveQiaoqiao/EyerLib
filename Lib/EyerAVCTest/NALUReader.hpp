#ifndef EYERLIB_NALUREADER_HPP
#define EYERLIB_NALUREADER_HPP

#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, NALUReader)
{
    // Eyer::EyerAnnexB annexB("./demo_video_176x144_baseline.h264");
    Eyer::EyerAnnexB annexB("./demo_video.h264");

    Eyer::EyerSPS sps;
    Eyer::EyerPPS pps;

    while(1){
        Eyer::EyerNALUData nalu;
        int ret = annexB.ReadNALU(nalu);
        if(ret){
            break;
        }

        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_SPS){
            sps.SetNALUData(nalu);
            sps.Parse();
            sps.PrintInfo();
        }
        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_PPS){
            pps.SetNALUData(nalu);
            pps.Parse();
            pps.PrintInfo();
        }
        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_SLICE){
            Eyer::EyerSLICE slice(sps, pps);
            slice.SetNALUData(nalu);
            slice.Parse();
            slice.PrintInfo();
        }
        if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_IDR){
            Eyer::EyerSLICE slice(sps, pps);
            slice.SetNALUData(nalu);
            slice.Parse();
            slice.PrintInfo();
        }
    }
}

#endif //EYERLIB_NALUREADER_HPP
