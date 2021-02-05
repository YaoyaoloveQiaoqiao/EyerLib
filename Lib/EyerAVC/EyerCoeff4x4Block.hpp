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

        int totleCoeff = 0;
        int trailingOnes = 0;

        int trailingSign[3] = {0};
        int levels[16] = {0};

        int totleZeros = 0;

        int runBefore[16] = {0};


        int luma_pred_mode = -1;
    };
}

#endif //EYERLIB_EYERCOEFF4X4BLOCK_HPP
