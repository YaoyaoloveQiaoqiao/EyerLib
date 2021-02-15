#include <gtest/gtest.h>
#include "EyerMath/EyerMath.hpp"

#include "EyerColorSpace/EyerColorSpace.hpp"

TEST(EyerColorSpace, init)
{
    Eyer::EyerColorSpace colorSpace;
    colorSpace.AddEatrix(colorSpace.rgb2020_xyz_mat);
    colorSpace.AddEatrix(!colorSpace.rgb709_xyz_mat);

    Eyer::EectorF3 rgb(0.5, 0.0, 0.0);
    Eyer::EectorF3 rgb_out = colorSpace.Convert(rgb);
    rgb_out.PrintInfo();

}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}