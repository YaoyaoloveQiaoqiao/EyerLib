#ifndef EYERLIB_EYERSLICE_HPP
#define EYERLIB_EYERSLICE_HPP

#include "EyerNALUData.hpp"
#include "EyerNALU.hpp"
#include "EyerBitStream.hpp"

#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "SLICEType.hpp"
#include "EyerSLICEHeader.hpp"
#include "EyerSLICEBody.hpp"

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
        EyerSLICEBody sliceBody;
    };
}

#endif //EYERLIB_EYERSLICE_HPP
