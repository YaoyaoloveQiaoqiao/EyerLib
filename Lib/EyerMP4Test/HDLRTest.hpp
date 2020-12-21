#ifndef EYERLIB_HDLRTEST_HPP
#define EYERLIB_HDLRTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxHDLR)
{
    EyerLog("=======================HDLR=======================\n");
    Eyer::MP4BoxHDLR hdlr;
    hdlr.SetDefaultData();
    hdlr.PrintInfo();

    Eyer::EyerBuffer buffer = hdlr.Serialize();

    Eyer::MP4BoxHDLR hdlr2;
    hdlr2.Parse(buffer);

    hdlr2.PrintInfo();

    ASSERT_EQ(hdlr, hdlr2) << "HDLR Error";

    eyer_log_clear();
}


#endif //EYERLIB_HDLRTEST_HPP
