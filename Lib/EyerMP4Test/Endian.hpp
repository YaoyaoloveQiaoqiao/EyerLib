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
        printf("a: %lld\n", a);
        printf("b: %lld\n", b);
        printf("c: %lld\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }
    {
        uint32_t a = 123;
        uint32_t b = Eyer::EyerUtil::EndianHtonl(a);
        uint32_t c = Eyer::EyerUtil::EndianNtohl(b);
        printf("a: %d\n", a);
        printf("b: %d\n", b);
        printf("c: %d\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }

    {
        uint16_t a = 123;
        uint16_t b = Eyer::EyerUtil::EndianHtons(a);
        uint16_t c = Eyer::EyerUtil::EndianNtohs(b);
        printf("a: %d\n", a);
        printf("b: %d\n", b);
        printf("c: %d\n", c);

        ASSERT_EQ(a, c) << "Error Endian";
    }

}

#endif //EYERLIB_ENDIAN_HPP
