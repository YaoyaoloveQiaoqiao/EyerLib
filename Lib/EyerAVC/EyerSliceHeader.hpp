#ifndef EYERLIB_EYERSLICEHEADER_HPP
#define EYERLIB_EYERSLICEHEADER_HPP

#include "EyerNALU.hpp"

namespace Eyer
{
    class EyerSliceHeader {
    public:
        EyerSliceHeader();
        ~EyerSliceHeader();
        EyerSliceHeader(const EyerSliceHeader & sliceHeader);
        EyerSliceHeader & operator = (const EyerSliceHeader & sliceHeader);

    public:
        int first_mb_in_slice = 0;
        int mb_aff_frame_flag = 0;
        int slice_type = 0;

        EyerNALU nalu;
    };
}

#endif //EYERLIB_EYERSLICEHEADER_HPP
