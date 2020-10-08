#ifndef EYERLIB_EYERSLICE_HPP
#define EYERLIB_EYERSLICE_HPP

#include "EyerNAL.hpp"
#include "EyerSLICEBase.hpp"
#include "EyerAVCCommon.hpp"

namespace Eyer
{
    class EyerSLICE : public EyerSLICEBase
    {
    public:
        EyerSLICE(EyerNALU & _nalu);
        ~EyerSLICE();

        virtual NaluType GetNalType();

        const SliceType & GetSliceType();
    };
}

#endif //EYERLIB_EYERSLICE_HPP
