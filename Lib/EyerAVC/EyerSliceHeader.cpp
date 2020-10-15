#include "EyerSliceHeader.hpp"

namespace Eyer
{
    EyerSliceHeader::EyerSliceHeader()
    {

    }

    EyerSliceHeader::~EyerSliceHeader()
    {

    }

    EyerSliceHeader::EyerSliceHeader(const EyerSliceHeader & sliceHeader) : EyerSliceHeader()
    {
        *this = sliceHeader;
    }

    EyerSliceHeader & EyerSliceHeader::operator = (const EyerSliceHeader & sliceHeader)
    {
        first_mb_in_slice       = sliceHeader.first_mb_in_slice;
        mb_aff_frame_flag       = sliceHeader.mb_aff_frame_flag;
        slice_type              = sliceHeader.slice_type;

        nalu                    = sliceHeader.nalu;

        return *this;
    }
}