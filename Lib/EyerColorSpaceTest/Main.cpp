#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

#include "EyerColorSpace/EyerColorSpace.hpp"

TEST(EyerColorSpace, init)
{
    Eyer::EyerColorSpace colorSpace;
    colorSpace.Convert();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}