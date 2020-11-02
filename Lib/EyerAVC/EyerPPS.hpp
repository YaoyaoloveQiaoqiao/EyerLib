#ifndef EYERLIB_EYERPPS_HPP
#define EYERLIB_EYERPPS_HPP

#include "EyerNALUData.hpp"
#include "EyerNALU.hpp"
#include "EyerBitStream.hpp"

namespace Eyer
{
    class EyerPPS : public EyerNALU {
    public:
        EyerPPS();
        ~EyerPPS();

        virtual int Parse();
    };
}



#endif //EYERLIB_EYERPPS_HPP
