#ifndef EYERLIB_NALUREADER_HPP
#define EYERLIB_NALUREADER_HPP

#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, NALUReader)
{
    // Eyer::EyerAnnexB annexB("./demo_video_176x144_baseline.h264");
    Eyer::EyerAnnexB annexB("./a_1.h264");
    // Eyer::EyerAnnexB annexB("./demo_video.h264");

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
        else if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_PPS){
            pps.SetNALUData(nalu);
            pps.Parse();
            pps.PrintInfo();
        }
        else if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_SLICE){
            Eyer::EyerSLICE slice(sps, pps);
            slice.SetNALUData(nalu);
            // slice.Parse();
            // slice.PrintInfo();
        }
        else if(nalu.GetNALUType() == Eyer::NALUType::NALU_TYPE_IDR){
            Eyer::EyerSLICE slice(sps, pps);
            slice.SetNALUData(nalu);
            slice.Parse();
            slice.PrintInfo();
        }
        else{
            continue;
        }

        /*
        Eyer::EyerString gopPath = Eyer::EyerString("./a_") + Eyer::EyerString::Number(gopId) + ".h264";
        FILE * f = fopen(gopPath.str, "a+");
        // unsigned char startcode[] = {0, 0, 0, 1};
        // fwrite(startcode, 4, 1, f);
        fwrite(nalu.GetNaluBuffer().GetPtr(), nalu.GetNaluBuffer().GetLen(), 1, f);
        fclose(f);
        */
    }

    eyer_log_clear();
}

#endif //EYERLIB_NALUREADER_HPP
