#ifndef EYERLIB_MVHDTEST_HPP
#define EYERLIB_MVHDTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxMVHD)
{
    EyerLog("=======================MVHD=======================\n");
    Eyer::MP4BoxMVHD mvhd;
    mvhd.SetDefaultData();
    mvhd.PrintInfo();

    Eyer::EyerBuffer buffer = mvhd.Serialize();

    Eyer::MP4BoxMVHD mvhd2;
    mvhd2.Parse(buffer);

    mvhd2.PrintInfo();

    ASSERT_EQ(mvhd, mvhd2) << "MVHD Error";

    eyer_log_clear();
}

#endif //EYERLIB_MVHDTEST_HPP
