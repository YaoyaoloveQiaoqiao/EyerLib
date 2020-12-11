#ifndef EYERLIB_EYERCOEFF4X4BLOCK_HPP
#define EYERLIB_EYERCOEFF4X4BLOCK_HPP

#include <stdio.h>
#include <stdint.h>

namespace Eyer
{
    class EyerCoeff4x4Block {
    public:
        EyerCoeff4x4Block();
        ~EyerCoeff4x4Block();

        bool emptyBlock = false;

        uint8_t numCoeff;
    };
}

#endif //EYERLIB_EYERCOEFF4X4BLOCK_HPP
