//
// Created by chuchun on 2020/12/30.
//

#ifndef EYERLIB_EYERPURECOLORBLOCK_HPP
#define EYERLIB_EYERPURECOLORBLOCK_HPP

#include <stdint.h>

namespace Eyer {
    class EyerPureColorBlock {
    public:
        EyerPureColorBlock(int _width, int _height);
        ~EyerPureColorBlock();

        int CopyData(int line, uint8_t * data);

        double GetAverage();

    public:
        int width = 0;
        int height = 0;
        unsigned char * blockContent = nullptr;
    };
}


#endif //EYERLIB_EYERPURECOLORBLOCK_HPP
