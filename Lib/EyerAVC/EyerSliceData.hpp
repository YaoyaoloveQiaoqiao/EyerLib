#ifndef EYERLIB_EYERSLICEDATA_HPP
#define EYERLIB_EYERSLICEDATA_HPP

#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSliceHeader.hpp"

namespace Eyer
{
    class EyerSliceData {
    public:
        EyerSliceData();
        ~EyerSliceData();

        int Parse(EyerSPS & _sps, EyerPPS & _pps, EyerSliceHeader & _sliceHeader, EyerBitStream * bitstream, int * used_bits);

    private:
        int MacroblockLayer(EyerBitStream * bitstream, int * used_bits);
    private:
        EyerSPS sps;
        EyerPPS pps;
    };
}

#endif //EYERLIB_EYERSLICEDATA_HPP
