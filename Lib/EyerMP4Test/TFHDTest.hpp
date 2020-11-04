//
// Created by Administrator on 2020/11/4.
//

#ifndef EYERLIB_TFHDTEST_HPP
#define EYERLIB_TFHDTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxTFHD){
    printf("=======================TFHD=======================\n");
    Eyer::MP4BoxTFHD tfhd;
    tfhd.SetDefaultData();
    tfhd.PrintInfo();

    Eyer::EyerBuffer buffer = tfhd.Serialize();

    Eyer::MP4BoxTFHD tfhd2;
    tfhd2.Parse(buffer);

    tfhd2.PrintInfo();

    ASSERT_EQ(tfhd, tfhd2) << "TFHD Error";
}

#endif //EYERLIB_TFHDTEST_HPP
