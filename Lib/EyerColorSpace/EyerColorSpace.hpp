//
// Created by chuchun on 2021/2/7.
//

#ifndef EYERLIB_EYERCOLORSPACE_H
#define EYERLIB_EYERCOLORSPACE_H

#include <iostream>
#include <cstdio>
#include <EyerMath/EyerMath.hpp>

namespace Eyer
{
    class EyerColorSpace
    {
    public:
        EyerColorSpace();
        ~EyerColorSpace();

        int AddEatrix(Eyer::Eatrix<float> & transformMat);
        Eyer::EectorF3 Convert(Eyer::EectorF3 rgb);

    public:
        Eyer::Eatrix<float> rgb2020_xyz_mat;
        Eyer::Eatrix<float> rgb709_xyz_mat;

    private:
        std::vector<Eyer::Eatrix<float>> transformEatrixVec;

    };

    class A
    {
    public:
        static A * instance;
        static A * GetInstance();

        Eyer::Eatrix<float> rgb2020_xyz_mat;
        Eyer::Eatrix<float> rgb709_xyz_mat;
    };

    A * A::instance = nullptr;
    A * A::GetInstance()
    {
        if(A::instance == nullptr){
            A::instance = new A();
            
        }
        return A::instance;
    }

    A::GetInstance()->rgb2020_xyz_mat


}
#endif //EYERLIB_EYERCOLORSPACE_H
