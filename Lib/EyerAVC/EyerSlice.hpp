#ifndef EYERLIB_EYERSLICE_HPP
#define EYERLIB_EYERSLICE_HPP

#include "EyerNALU.hpp"
#include "EyerNAL.hpp"

namespace Eyer{
    class EyerSlice : public EyerNAL{
    public:
        EyerSlice(EyerNALU & nalu);
        ~EyerSlice();

        virtual NaluType GetNalType();
    };
}

#endif //EYERLIB_EYERSLICE_HPP
