#ifndef EYERLIB_FTYPTEST_HPP
#define EYERLIB_FTYPTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, EyerMP4_FTYP)
{
    printf("=======================FTYP=======================\n");
    Eyer::MP4BoxFTYP ftyp;
    ftyp.SetDefaultData();
    ftyp.PrintInfo();

    Eyer::EyerBuffer buffer = ftyp.Serialize();

    Eyer::MP4BoxFTYP ftyp2;
    ftyp2.Parse(buffer);

    ftyp2.PrintInfo();

    ASSERT_EQ(ftyp, ftyp2) << "FTYP Error";
}

#endif //EYERLIB_FTYPTEST_HPP
