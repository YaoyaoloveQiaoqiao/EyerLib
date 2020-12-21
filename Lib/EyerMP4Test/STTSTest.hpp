#ifndef EYERLIB_STTSTEST_HPP
#define EYERLIB_STTSTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxSTTS)
{
    EyerLog("=======================STTS=======================\n");
    Eyer::MP4BoxSTTS stts;
    stts.SetDefaultData();
    stts.PrintInfo();

    Eyer::EyerBuffer buffer = stts.Serialize();

    Eyer::MP4BoxSTTS stts2;
    stts2.Parse(buffer);

    stts2.PrintInfo();

    ASSERT_EQ(stts, stts2) << "STTS Error";

    eyer_log_clear();
}

#endif //EYERLIB_STTSTEST_HPP
