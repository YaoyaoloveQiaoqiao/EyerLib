#ifndef EYERLIB_EYERSLICE_HPP
#define EYERLIB_EYERSLICE_HPP

#include "EyerNAL.hpp"
#include "EyerSLICEBase.hpp"

namespace Eyer
{
    class EyerSLICE : public EyerSLICEBase
    {
    public:
        EyerSLICE(EyerNALU & _nalu);
        ~EyerSLICE();

        virtual NaluType GetNalType();
    };
}

#endif //EYERLIB_EYERSLICE_HPP
