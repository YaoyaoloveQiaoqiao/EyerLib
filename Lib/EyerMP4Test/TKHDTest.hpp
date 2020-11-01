#ifndef EYERLIB_TKHDTEST_HPP
#define EYERLIB_TKHDTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxTKHD)
{
    printf("=======================TKHD=======================\n");
    Eyer::MP4BoxTKHD tkhd;
    tkhd.SetDefaultData();
    tkhd.PrintInfo();

    Eyer::EyerBuffer buffer = tkhd.Serialize();

    Eyer::MP4BoxTKHD tkhd2;
    tkhd2.Parse(buffer);

    tkhd2.PrintInfo();

    ASSERT_EQ(tkhd, tkhd2) << "TKHD Error";
    ASSERT_EQ(tkhd.Serialize().GetLen() , 92) << "TKHD Len Error";
    ASSERT_EQ(tkhd2.Serialize().GetLen(), 92) << "TKHD Len Error";
}

#endif //EYERLIB_TKHDTEST_HPP
