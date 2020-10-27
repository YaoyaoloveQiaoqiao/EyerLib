#ifndef EYERLIB_ELSTTEST_HPP
#define EYERLIB_ELSTTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, MP4BoxELST)
{
    printf("=======================ELST=======================\n");
    Eyer::MP4BoxELST elst;
    elst.SetDefaultData();
    elst.PrintInfo();

    Eyer::EyerBuffer buffer = elst.Serialize();

    Eyer::MP4BoxELST elst2;
    elst2.Parse(buffer);

    elst2.PrintInfo();

    ASSERT_EQ(elst, elst2) << "ELST Error";
}

#endif //EYERLIB_ELSTTEST_HPP
