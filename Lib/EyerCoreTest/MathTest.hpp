#ifndef	EYER_CORE_TEST_MATH_H
#define	EYER_CORE_TEST_MATH_H

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"

TEST(EyerMath, Mat_Base){
    for(int i=0;i<100;i++){
        Eyer::EyerMat mat(4, 4);
    }

    Eyer::EyerVec2 a;
    EyerLog("EyerVec2 x:%f\n", a.x());

    Eyer::EyerMat m(3, 3);
    m.mat[0][0] = 1.2f;
    m.Print();

    Eyer::EyerVec3 vec3;
    vec3.SetX(1);
    vec3.SetY(2);
    vec3.SetZ(3);

    vec3.Print();

    Eyer::EyerMat res = m * vec3;

    res.Print();
}

#endif