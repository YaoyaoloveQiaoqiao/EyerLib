#ifndef EYERLIB_EYERSLICEBODY_HPP
#define EYERLIB_EYERSLICEBODY_HPP

#include "EyerBitStream.hpp"
#include "EyerField.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSLICEHeader.hpp"
#include "MB_TYPE.hpp"

namespace Eyer
{
    class EyerSLICEBody {
    public:
        EyerSLICEBody();
        ~EyerSLICEBody();

        int Parse(EyerBitStream & bs, EyerFieldList & fieldList, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);

    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        int macroblock_layer(SLICEType sliceType, EyerBitStream & bs);
        int mb_pred(MB_TYPE mbType, EyerBitStream & bs);
    };
}

#endif //EYERLIB_EYERSLICEBODY_HPP
