#ifndef EYERLIB_READ_FMP4TEST_HPP
#define EYERLIB_READ_FMP4TEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, EyerReadfMP4)
{
    printf("=======================Read fMP4=======================\n");
    // FILE * fp = fopen("/Users/lichi/annie/xiaomai.mp4", "rb");
    FILE * fp = fopen("./xiaomai_dashinit.mp4", "rb");

    // FILE * fp = fopen("./demo.mp4", "rb");

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);

    fseek(fp, 0, 0);

    unsigned char * data = (unsigned char *)malloc(len);
    int ret = fread(data, len, 1, fp);

    Eyer::EyerBuffer buffer;
    buffer.Append(data, len);

    Eyer::MP4Box box;
    box.ParseSubBox(buffer);
    box.PrintInfo();

    Eyer::MP4Box * moovBox = box.GetSubBoxPtr(Eyer::BoxType::MOOV);

    Eyer::MP4Box moovbox2 = *moovBox;

    free(data);

    fclose(fp);
}


#endif //EYERLIB_READ_FMP4TEST_HPP
