#ifndef EYERLIB_EYERIDR_HPP
#define EYERLIB_EYERIDR_HPP

#include "EyerNAL.hpp"
#include "EyerSLICEBase.hpp"

namespace Eyer
{
    class EyerIDR : public EyerSLICEBase
    {
    public:
        EyerIDR(EyerNALU & _nalu);
        ~EyerIDR();

        virtual NaluType GetNalType();
    };
}

#endif //EYERLIB_EYERIDR_HPP
