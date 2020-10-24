#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"


TEST(EyerMP4, EyerMP4Test)
{
    printf("=======================Read File=======================\n");
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

    free(data);

    fclose(fp);
}

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

TEST(EyerMP4, MP4BoxMVHD)
{
    printf("=======================MVHD=======================\n");
    Eyer::MP4BoxMVHD mvhd;
    mvhd.SetDefaultData();
    mvhd.PrintInfo();

    Eyer::EyerBuffer buffer = mvhd.Serialize();

    Eyer::MP4BoxMVHD mvhd2;
    mvhd2.Parse(buffer);

    mvhd2.PrintInfo();

    ASSERT_EQ(mvhd, mvhd2) << "MVHD Error";
}

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
}

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

TEST(EyerMP4, MP4BoxHDLR)
{
    printf("=======================HDLR=======================\n");
    Eyer::MP4BoxHDLR hdlr;
    hdlr.SetDefaultData();
    hdlr.PrintInfo();

    Eyer::EyerBuffer buffer = hdlr.Serialize();

    Eyer::MP4BoxHDLR hdlr2;
    hdlr2.Parse(buffer);

    hdlr2.PrintInfo();

    ASSERT_EQ(hdlr, hdlr2) << "HDLR Error";
}

TEST(EyerMP4, MP4BoxTREX)
{
    printf("=======================TREX=======================\n");
    Eyer::MP4BoxTREX trex;
    trex.SetDefaultData();
    trex.PrintInfo();

    Eyer::EyerBuffer buffer = trex.Serialize();

    Eyer::MP4BoxTREX trex2;
    trex2.Parse(buffer);

    trex2.PrintInfo();

    ASSERT_EQ(trex, trex2) << "HDLR Error";
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
