#ifndef EYERLIB_TREXTEST_HPP
#define EYERLIB_TREXTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxTREX)
{
    EyerLog("=======================TREX=======================\n");
    Eyer::MP4BoxTREX trex;
    trex.SetDefaultData();
    trex.PrintInfo();

    Eyer::EyerBuffer buffer = trex.Serialize();

    Eyer::MP4BoxTREX trex2;
    trex2.Parse(buffer);

    trex2.PrintInfo();

    ASSERT_EQ(trex, trex2) << "HDLR Error";

    eyer_log_clear();
}

#endif //EYERLIB_TREXTEST_HPP
