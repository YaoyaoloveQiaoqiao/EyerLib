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

        int AddEatrix(const Eyer::Eatrix<float> & transformMat);
        Eyer::EectorF3 Convert(Eyer::EectorF3 rgb);

    private:
        std::vector<Eyer::Eatrix<float>> transformEatrixVec;

    };

    class EyerColorSpaceMat
    {
    private:
        EyerColorSpaceMat();
    public:
        static EyerColorSpaceMat * instance;
        static EyerColorSpaceMat * GetInstance();

        Eyer::Eatrix<float> rgb2020_xyz_mat;
        Eyer::Eatrix<float> rgb709_xyz_mat;
    };

}
#endif //EYERLIB_EYERCOLORSPACE_H
