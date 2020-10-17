#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

#define MAX_BOX_SIZE_LEN 4
#define MAX_BOX_TYPE_LEN 4

#define BOX_TYPE_FTYPE "ftyp"
#define BOX_TYPE_MOOV "moov"
#define BOX_TYPE_MVHD "mvhd"
#define BOX_TYPE_TRAK "trak"
#define BOX_TYPE_TKHD "tkhd"
#define BOX_TYPE_EDTS "edts"
#define BOX_TYPE_MDIA "mdia"
#define BOX_TYPE_MDHD "mdhd"
#define BOX_TYPE_HDLR "hdlr"
#define BOX_TYPE_MINF "minf"
#define BOX_TYPE_VMHD "vmhd"
#define BOX_TYPE_DINF "dinf"
#define BOX_TYPE_DREF "dref"
#define BOX_TYPE_STBL "stbl"
#define BOX_TYPE_STSD "stsd"
#define BOX_TYPE_STTS "stts"
#define BOX_TYPE_STSS "stss"
#define BOX_TYPE_STSC "stsc"
#define BOX_TYPE_STSZ "stsz"
#define BOX_TYPE_STCO "stco"
#define BOX_TYPE_UDTA "udta"


TEST(EyerMP4, EyerMP4Test)
{
    FILE * fp = fopen("/Users/yuqiaomiao/boy.mp4", "rb");
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);

    fseek(fp, 0, 0);

    unsigned char * data = (unsigned char *)malloc(len);
    int ret = fread(data, len, 1, fp);

    Eyer::EyerBuffer buffer;
    buffer.Append(data, len);

    Eyer::EyerMP4Deserialize deserialize(buffer);

    while(1){
        Eyer::EyerMP4Box box;
        int ret = deserialize.Get(box);
        if(ret){
            break;
        }
    }

    free(data);

    fclose(fp);
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
