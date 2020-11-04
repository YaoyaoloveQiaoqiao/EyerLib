//
// Created by Administrator on 2020/10/29.
//

#ifndef EYERLIB_MFHDTEST_HPP
#define EYERLIB_MFHDTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxMFHD)
{
printf("=======================MFHD=======================\n");
Eyer::MP4BoxMFHD mfhd;
mfhd.SetDefaultData();
mfhd.PrintInfo();

Eyer::EyerBuffer buffer = mfhd.Serialize();
/*unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
buffer.GetBuffer(data);*/
/*for(int i=0; i<buffer.GetLen(); i++){
    printf("buffer: %c", data[i]);
}*/
Eyer::MP4BoxMFHD mfhd2;
mfhd2.Parse(buffer);

mfhd2.PrintInfo();

ASSERT_EQ(mfhd, mfhd2) << "MFHD Error";
}

#endif //EYERLIB_MFHDTEST_HPP
