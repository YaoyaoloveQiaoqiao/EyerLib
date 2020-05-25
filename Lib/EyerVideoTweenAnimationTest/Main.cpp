#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerVideoTweenAnimation/EyerVideoTweenAnimation.hpp"

TEST(EyerVideoTweenAnimation, EyerVideoTweenAnimation){
    Eyer::EyerVideoTweenAnimation a ;
    Eyer::EyerVideoAnimationKey key;
    a.AddKey(key);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}