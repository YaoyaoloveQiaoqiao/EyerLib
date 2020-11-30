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
        ret = reader.ReadNalu(buffer, &bufferLen);
        if(ret){
            break;
        }
        printf("Buffer Len: %d\n", bufferLen);
        printf("%d %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
    }

    reader.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}