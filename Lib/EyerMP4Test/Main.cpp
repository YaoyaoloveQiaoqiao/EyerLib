#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

TEST(EyerMP4, EyerMP4Test)
{
    FILE * fp = fopen("./demo.mp4", "rb");


    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);

    fseek(fp, 0, 0);

    unsigned char * data = (unsigned char *)malloc(len);
    int ret = fread(data, len, 1, fp);

    Eyer::EyerBuffer buffer;
    buffer.Append(data, len);

    Eyer::MP4BoxFTYP box;
    // box.Parse(buffer);
    box.ParseSubBox(buffer, 0);

    free(data);

    fclose(fp);
}



int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
