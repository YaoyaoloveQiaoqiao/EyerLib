#ifndef EYERLIB_BASELINE_HPP
#define EYERLIB_BASELINE_HPP

#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, Demo_video_176x144_baseline)
{
    Eyer::EyerAVCDecoder avcDeocder("./demo_video_176x144_baseline.h264");
    avcDeocder.Decode();
}

#endif //EYERLIB_BASELINE_HPP
