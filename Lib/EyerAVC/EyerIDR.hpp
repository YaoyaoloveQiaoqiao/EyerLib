#ifndef EYERLIB_EYERIDR_HPP
#define EYERLIB_EYERIDR_HPP

#include "EyerNAL.hpp"

namespace Eyer
{
    class EyerIDR : public EyerNAL
    {
    public:
        EyerIDR(EyerNALU & _nalu);
        ~EyerIDR();

        virtual NaluType GetNalType();
    };
}

#endif //EYERLIB_EYERIDR_HPP
