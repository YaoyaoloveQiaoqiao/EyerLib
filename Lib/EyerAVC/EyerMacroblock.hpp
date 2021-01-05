#ifndef EYERLIB_EYERMACROBLOCK_HPP
#define EYERLIB_EYERMACROBLOCK_HPP

#include "EyerBitStream.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSLICEHeader.hpp"

#include "MB_TYPE.hpp"
#include "EyerCoeff4x4Block.hpp"
#include "RESIDUAL_TYPE.hpp"

namespace Eyer
{
    class EyerMacroblock;

    class EyerMacroblock {
    public:
        EyerMacroblock();
        EyerMacroblock(int _mbIndex, EyerMacroblock * _mbAddrA, EyerMacroblock * _mbAddrB, EyerMacroblock * _mbAddrC, EyerMacroblock * _mbAddrD);
        ~EyerMacroblock();

        int Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);

        EyerCoeff4x4Block * findBlock(int blockX, int blockY, RESIDUAL_TYPE & type);

    private:
        int MbPred       (EyerBitStream & bs);
        int Residual     (EyerBitStream & bs, int startIdx, int endIdx);

        int ResidualLuma (EyerBitStream & bs, int startIdx, int endIdx);

        int ResidualBlockCavlc(EyerBitStream & bs, int & totleCoeff, int nC, int startIdx, int endIdx, int maxNumCoeff);

        int GetNumberCurrent(int i8x8, int i4x4, RESIDUAL_TYPE & type);

        int get_coeff_level(EyerBitStream & bs, int &level, int levelIdx, int trailingOnes, int suffixLength);

        int get_total_zeros(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx);

        int get_run_before(EyerBitStream & bs, int & runBefore, int runBefore_vlcIdx);
    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        EyerMacroblock * mbAddrA = nullptr;
        EyerMacroblock * mbAddrB = nullptr;
        EyerMacroblock * mbAddrC = nullptr;
        EyerMacroblock * mbAddrD = nullptr;

        int mbIndex = 0;

        uint8_t transform_size_8x8_flag = 0;

        MB_TYPE mbType = MB_TYPE::I_NxN;
        uint32_t CodedBlockPatternLuma = 0;
        uint32_t CodedBlockPatternChroma = 0;

        uint32_t intra_chroma_pred_mode = 0;

        EyerCoeff4x4Block lumaResidual[4][4];
        EyerCoeff4x4Block chromaCrResidual[4][4];
        EyerCoeff4x4Block chromaCbResidual[4][4];
    };
}


#endif //EYERLIB_EYERMACROBLOCK_HPP
