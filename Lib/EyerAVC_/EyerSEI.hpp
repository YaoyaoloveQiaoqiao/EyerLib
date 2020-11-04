#ifndef EYERLIB_EYERSEI_HPP
#define EYERLIB_EYERSEI_HPP

#include "EyerNAL.hpp"

namespace Eyer{
    class EyerSEI : public EyerNAL{
    public:
        EyerSEI(EyerNALU & nalu);
        ~EyerSEI();

        virtual NaluType GetNalType();
    };
}

#endif //EYERLIB_EYERSEI_HPP
