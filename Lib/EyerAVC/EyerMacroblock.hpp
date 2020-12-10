#ifndef EYERLIB_EYERMACROBLOCK_HPP
#define EYERLIB_EYERMACROBLOCK_HPP

#include "EyerBitStream.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSLICEHeader.hpp"
#include "MB_TYPE.hpp"
#include "EyerCoeff4x4Block.hpp"

namespace Eyer
{
    class EyerMacroblock {
    public:
        EyerMacroblock(int _mbIndex);
        ~EyerMacroblock();

        int Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);

    private:
        int mb_pred     (EyerBitStream & bs);
        int residual    (EyerBitStream & bs);

        int get_luma_coeff(int x, int y);

        int GetNumberCurrent(int x, int y);
        int GetNeighborAvailable(bool & available_top, bool & available_left, int & topIndex, int & leftIndex, int blockIndexX, int blockIndexY);

    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        int mbIndex = 0;

        MB_TYPE mbType = MB_TYPE::I_NxN;
        uint32_t CodecBlockPatterLuma = 0;
        uint32_t CodecBlockPatterChroma = 0;

        EyerCoeff4x4Block lumaResidual[4][4];
    };
}


#endif //EYERLIB_EYERMACROBLOCK_HPP
