#ifndef EYERLIB_ENDIAN_HPP
#define EYERLIB_ENDIAN_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, Endian)
{
    {
        uint64_t a = 123;
        uint64_t b = Eyer::EyerUtil::EndianHtonll(a);
        uint64_t c = Eyer::EyerUtil::EndianNtohll(b);
        EyerLog("a: %lld\n", a);
        EyerLog("b: %lld\n", b);
        EyerLog("c: %lld\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }
    {
        uint32_t a = 123;
        uint32_t b = Eyer::EyerUtil::EndianHtonl(a);
        uint32_t c = Eyer::EyerUtil::EndianNtohl(b);
        EyerLog("a: %d\n", a);
        EyerLog("b: %d\n", b);
        EyerLog("c: %d\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }

    {
        uint16_t a = 123;
        uint16_t b = Eyer::EyerUtil::EndianHtons(a);
        uint16_t c = Eyer::EyerUtil::EndianNtohs(b);
        EyerLog("a: %d\n", a);
        EyerLog("b: %d\n", b);
        EyerLog("c: %d\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }

    eyer_log_clear();
}

#endif //EYERLIB_ENDIAN_HPP
