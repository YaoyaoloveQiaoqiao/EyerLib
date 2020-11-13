#ifndef EYERLIB_EYERSLICE_HPP
#define EYERLIB_EYERSLICE_HPP

#include "EyerNALUData.hpp"
#include "EyerNALU.hpp"
#include "EyerBitStream.hpp"

#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "SLICEType.hpp"
#include "EyerSLICEHeader.hpp"

namespace Eyer
{
    class EyerSLICE : public EyerNALU {
    public:
        EyerSLICE(EyerSPS & _sps, EyerPPS & _pps);
        ~EyerSLICE();

        SLICEType GetSLICEType();

        virtual int Parse();

    private:
        EyerSPS sps;
        EyerPPS pps;

        EyerSLICEHeader sliceHeader;

        int ParseBody(EyerBitStream & bs);
    };
}

#endif //EYERLIB_EYERSLICE_HPP
