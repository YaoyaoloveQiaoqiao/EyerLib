#ifndef EYERLIB_MEHDTEST_HPP
#define EYERLIB_MEHDTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxMEHD)
{
    EyerLog("=======================MEHD=======================\n");
    Eyer::MP4BoxMEHD mehd;
    mehd.SetDefaultData();
    mehd.PrintInfo();

    Eyer::EyerBuffer buffer = mehd.Serialize();

    Eyer::MP4BoxMEHD mehd2;
    mehd2.Parse(buffer);

    mehd2.PrintInfo();

    ASSERT_EQ(mehd, mehd2) << "MEHD Error";

    eyer_log_clear();
}

#endif //EYERLIB_MEHDTEST_HPP
