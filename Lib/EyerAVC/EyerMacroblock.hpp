#ifndef EYERLIB_EYERMACROBLOCK_HPP
#define EYERLIB_EYERMACROBLOCK_HPP

#include "Sample.hpp"
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
        EyerMacroblock(int _mbIndex, EyerMacroblock * _mbAddrA, EyerMacroblock * _mbAddrB, EyerMacroblock * _mbAddrC, EyerMacroblock * _mbAddrD, EyerMacroblock * _mbAddrF);
        ~EyerMacroblock();

        int Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);
        int Decode();

        EyerCoeff4x4Block * findBlock(int blockX, int blockY, RESIDUAL_TYPE & type);

    private:
        int MbPred       (EyerBitStream & bs);

        int Residual     (EyerBitStream & bs, int startIdx, int endIdx);

        int ResidualLuma (EyerBitStream & bs, int startIdx, int endIdx);

        int ResidualBlockCavlc(EyerBitStream & bs, EyerCoeff4x4Block & coeff4x4Block, int nC, int startIdx, int endIdx, int maxNumCoeff, bool isChromaDC = false);

        int GetNumberCurrent(int i8x8, int i4x4, RESIDUAL_TYPE & type);

        int GetTopLeftBlock(EyerCoeff4x4Block ** top, EyerCoeff4x4Block ** left, int i8x8, int i4x4, RESIDUAL_TYPE & type);

        int GetABCDBlock (EyerCoeff4x4Block ** a, EyerCoeff4x4Block ** b, EyerCoeff4x4Block ** c, EyerCoeff4x4Block ** d, int i8x8, int i4x4, RESIDUAL_TYPE & type);

    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        EyerMacroblock * mbAddrA = nullptr;
        EyerMacroblock * mbAddrB = nullptr;
        EyerMacroblock * mbAddrC = nullptr;
        EyerMacroblock * mbAddrD = nullptr;
        EyerMacroblock * mbAddrF = nullptr;

        int mbIndex = 0;

        int qp = 0;

        uint8_t transform_size_8x8_flag = 0;

        MB_TYPE mbType = MB_TYPE::I_NxN;
        uint32_t CodedBlockPatternLuma = 0;
        uint32_t CodedBlockPatternChroma = 0;

        uint32_t intra_chroma_pred_mode = 0;


        EyerCoeff4x4Block lumaResidual[4][4];

        EyerCoeff4x4Block chromaResidualDC[2];

        EyerCoeff4x4Block chromaCrResidualAC[4][4];
        EyerCoeff4x4Block chromaCbResidualAC[4][4];

        int swap(int & x, int & y);
        int MIN(int a, int b);

        int GetSample(int x, int y, Sample & sample);

    public:
        EyerTable<Sample> predTable;
    };
}


#endif //EYERLIB_EYERMACROBLOCK_HPP
