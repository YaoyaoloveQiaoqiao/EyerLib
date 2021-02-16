#include "EyerColorSpace.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer {

    EyerColorSpace::EyerColorSpace() {

    }

    EyerColorSpace::~EyerColorSpace() {
        transformEatrixVec.clear();
    }

    int EyerColorSpace::AddEatrix(const Eyer::Eatrix<float> &transformMat) {
        transformEatrixVec.push_back(transformMat);
        return 0;
    }

    Eyer::EectorF3 EyerColorSpace::Convert(Eyer::EectorF3 rgb) {
        Eyer::EectorF3 outRgb = rgb;
        for (int i = 0; i < transformEatrixVec.size(); i++) {
            EyerLog("=========================i:%d\n", i);
            //outRgb.PrintInfo();
            transformEatrixVec[i].PrintInfo();
            outRgb = transformEatrixVec[i] * outRgb;
        }
        return outRgb;
    }

}