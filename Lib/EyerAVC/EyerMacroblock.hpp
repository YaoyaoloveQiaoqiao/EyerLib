#ifndef EYERLIB_EYERMACROBLOCK_HPP
#define EYERLIB_EYERMACROBLOCK_HPP

#include "EyerBitStream.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSLICEHeader.hpp"
#include "MB_TYPE.hpp"

namespace Eyer
{
    class EyerMacroblock {
    public:
        EyerMacroblock();
        ~EyerMacroblock();

        int Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);

    private:
        int mb_pred     (EyerBitStream & bs);
        int residual    (EyerBitStream & bs);

    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        MB_TYPE mbType = MB_TYPE::I_NxN;
        uint32_t CodecBlockPatterLuma = 0;
        uint32_t CodecBlockPatterChroma = 0;
    };
}


#endif //EYERLIB_EYERMACROBLOCK_HPP
