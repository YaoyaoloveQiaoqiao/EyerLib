#include <stdio.h>
#include <gtest/gtest.h>
#include "MBType/MBType.hpp"

TEST(MBType, MBType){
    MB::MBType type("/home/redknot/Manjari-Bold.otf");
    int ret = type.Init();
    ASSERT_EQ(ret, 0) << "Init Ret Error";

    int index = type.GenChar('0', 200);
    ASSERT_GT(index, 0) << "GenChar Error";
    
    MBLog("GenChar Index: %d\n", index);

    MB::MBTypeBitmap bitmap;
    ret = type.GetCharBitmap(index, &bitmap);
    ASSERT_EQ(ret, 0) << "GetCharBitmap Ret Error";

    MBLog("Width: %d\n",bitmap.width);
    MBLog("Height: %d\n", bitmap.height);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}