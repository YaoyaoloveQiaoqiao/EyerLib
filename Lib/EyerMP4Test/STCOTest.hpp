#ifndef EYERLIB_STCOTEST_HPP
#define EYERLIB_STCOTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxSTCO)
{
    EyerLog("=======================STCO=======================\n");
    Eyer::MP4BoxSTCO stco;
    stco.SetDefaultData();
    stco.PrintInfo();

    Eyer::EyerBuffer buffer = stco.Serialize();

    Eyer::MP4BoxSTCO stco2;
    stco2.Parse(buffer);

    stco2.PrintInfo();

    ASSERT_EQ(stco, stco2) << "STCO Error";

    eyer_log_clear();
}

#endif //EYERLIB_STCOTEST_HPP
