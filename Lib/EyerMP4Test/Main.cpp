#include <gtest/gtest.h>

TEST(EyerMP4, EyerMP4Test)
{
    FILE *file = fopen(".mp4","rb");
    fseek(file,0L,SEEK_END);
    long filesize = ftell(file);
    fseek(file,0L,SEEK_SET);
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
