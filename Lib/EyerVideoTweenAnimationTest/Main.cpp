#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerVideoTweenAnimation/EyerVideoTweenAnimation.hpp"

TEST(EyerVideoTweenAnimation, EyerVideoTweenAnimation){
    Eyer::EyerVideoTweenAnimation a ;
    Eyer::EyerVideoAnimationKey key1(1.0, 1, 1, 1);
    Eyer::EyerVideoAnimationKey key2(2.0, 2, 2, 2);
    Eyer::EyerVideoAnimationKey key4(4.0, 4, 4, 4);

    a.AddKey(key1);
    a.AddKey(key2);
    a.AddKey(key4);

    Eyer::EyerVideoAnimationKey keyout;
    a.GetLinearValue(3.0, keyout);
    printf("keyout x： %f, y： %f, z：%f", keyout.x, keyout.y, keyout.z);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}