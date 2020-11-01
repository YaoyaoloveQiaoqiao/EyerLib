#ifndef EYERLIB_NALUREADER_HPP
#define EYERLIB_NALUREADER_HPP

#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, NALUReader)
{
    Eyer::EyerAnnexB annexB("./demo_video_176x144_baseline.h264");

    while(1){
        Eyer::EyerNALU nalu;
        int ret = annexB.ReadNALU(nalu);
        if(ret){
            break;
        }
    }
}

#endif //EYERLIB_NALUREADER_HPP
