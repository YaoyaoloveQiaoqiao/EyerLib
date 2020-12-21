#ifndef EYERLIB_READ_MP4TEST_HPP
#define EYERLIB_READ_MP4TEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, EyerReadMP4)
{
    EyerLog("=======================Read MP4=======================\n");
    // FILE * fp = fopen("./xiaomai_dashinit.mp4", "rb");
    // FILE * fp = fopen("/Users/lichi/Desktop/size_merge.mp4", "rb");
    FILE * fp = fopen("./demo.mp4", "rb");
    // FILE * fp = fopen("/Users/lichi/Desktop/huyou_error.mp4", "rb");

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

    /*
    {
        Eyer::MP4Box * a = box.GetSubBoxPtr(Eyer::BoxType::MOOV)->GetSubBoxPtr(Eyer::BoxType::TRAK);

        Eyer::MP4Box moov(Eyer::BoxType::MOOV);
        moov.AddSubBox(a);
        moov.AddSubBox(a);
    }
    */

    free(data);

    fclose(fp);

    eyer_log_clear();
}

#endif //EYERLIB_READ_MP4TEST_HPP
