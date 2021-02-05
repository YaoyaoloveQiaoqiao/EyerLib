//
// Created by chuchun on 2020/12/30.
//

#ifndef EYERLIB_EYERPURECOLORCHECK_H
#define EYERLIB_EYERPURECOLORCHECK_H

#include <stdint.h>
#include "EyerPureColorBlock.hpp"
#include <vector>

namespace Eyer {
    class EyerPureColorRes {
    public:
        double standardDeviation = 0;
    };

    class EyerPureColorCheck {
    public:
        EyerPureColorCheck();
        ~EyerPureColorCheck();

        int GetChannelRes(EyerPureColorRes & res, uint8_t * channelData, int width, int height);

    private:
        std::vector<EyerPureColorBlock *> blockList;
    };
}

#endif //EYERLIB_EYERPURECOLORCHECK_H
