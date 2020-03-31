#ifndef	EYER_CORE_TEST_MATH_H
#define	EYER_CORE_TEST_MATH_H

#include <gtest/gtest.h>

#include "MBCore/MBCore.hpp"

TEST(MBMath, Mat_Base){
    for(int i=0;i<100;i++){
        MB::MBMat mat(4, 4);
    }

    MB::MBVec2 a;
    MBLog("MBVec2 x:%f\n", a.x());
}

#endif