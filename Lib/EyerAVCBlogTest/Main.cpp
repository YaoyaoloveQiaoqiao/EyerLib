#include <gtest/gtest.h>
#include "EyerAVCBlog/AnnexBReader.hpp"

TEST(AVCBlog, AVCBlogAnnexB)
{
    printf("Eyer AnnexB Test\n");

    std::string filePath = "./demo_video_176x144_baseline.h264";
    AnnexBReader reader(filePath);
    int ret = reader.Open();
    if(ret){
        printf("Read Fail");
        return;
    }

    while(1){
        uint8_t buffer[1024 * 1024];
        int bufferLen = 0;
        int startcodeLen = 0;
        ret = reader.ReadNalu(buffer, &bufferLen, &startcodeLen);
        if(ret){
            break;
        }
        printf("=====================\n");
        printf("Buffer Len: %d\n", bufferLen);
        printf("Start Code Len: %d\n", startcodeLen);
        printf("%d %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

        int forbidden_bit   = (*(buffer + startcodeLen) >> 7) & 1;
        int nal_ref_idc     = (*(buffer + startcodeLen) >> 5) & 3;
        int nal_unit_type   = (*(buffer + startcodeLen) >> 0) & 0x1f;

        printf("forbidden_bit: %d\n", forbidden_bit);
        printf("nal_ref_idc: %d\n", nal_ref_idc);
        printf("nal_unit_type: %d\n", nal_unit_type);
    }

    reader.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}