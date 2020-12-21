#ifndef EYERLIB_STSCTEST_HPP
#define EYERLIB_STSCTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxSTSC)
{
    EyerLog("=======================STSC=======================\n");
    Eyer::MP4BoxSTSC stsc;
    stsc.SetDefaultData();
    stsc.PrintInfo();

    Eyer::EyerBuffer buffer = stsc.Serialize();

    Eyer::MP4BoxSTSC stsc2;
    stsc2.Parse(buffer);

    stsc2.PrintInfo();

    ASSERT_EQ(stsc, stsc2) << "STSC Error";

    eyer_log_clear();
}

#endif //EYERLIB_STSCTEST_HPP
