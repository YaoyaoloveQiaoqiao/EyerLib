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

    Eyer::EyerVideoAnimationKey keyout3(3.0, 0.0, 0, 0);
    Eyer::EyerVideoAnimationKey keyout4(4.0, 0.0, 0, 0);
    Eyer::EyerVideoAnimationKey keyout5(5.0, 0.0, 0, 0);
    Eyer::EyerVideoAnimationKey keyout6(6.0, 0.0, 0, 0);
    a.GetLinearValue(keyout3);
    EXPECT_EQ(keyout3.x, 3.0);
    printf("keyout3 x： %f, y： %f, z：%f \n", keyout3.x, keyout3.y, keyout3.z);

    a.GetLinearValue(keyout4);
    EXPECT_EQ(keyout4.x, 4.0);
    printf("keyout4 x： %f, y： %f, z：%f\n", keyout4.x, keyout4.y, keyout4.z);

    a.GetLinearValue(keyout5);
    EXPECT_EQ(keyout5.x, 4.0);
    printf("keyout5 x： %f, y： %f, z：%f\n", keyout5.x, keyout5.y, keyout5.z);

    a.GetLinearValue(keyout6);
    EXPECT_EQ(keyout6.x, 4.0);
    printf("keyout6 x： %f, y： %f, z：%f\n", keyout6.x, keyout6.y, keyout6.z);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}