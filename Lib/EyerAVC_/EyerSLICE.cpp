#include "EyerSLICE.hpp"

#include "EyerAVC_VLC.hpp"
#include "EyerNALU.hpp"

namespace Eyer
{
    NaluType EyerSLICE::GetNalType()
    {
        return NaluType::NALU_TYPE_SLICE;
    }

    EyerSLICE::EyerSLICE(EyerNALU & _nalu, EyerSPS & _sps, EyerPPS & _pps) : EyerSLICEBase(_nalu, _sps, _pps)
    {

    }

    EyerSLICE::~EyerSLICE()
    {

    }

    SliceType EyerSLICE::GetSliceType()
    {
        return (SliceType)slice_type;
    }
}