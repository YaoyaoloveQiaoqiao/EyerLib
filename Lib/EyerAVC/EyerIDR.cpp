#include "EyerIDR.hpp"
#include "EyerAVC_VLC.hpp"

#include "EyerSLICE.hpp"

namespace Eyer
{
    NaluType EyerIDR::GetNalType()
    {
        return NaluType::NALU_TYPE_IDR;
    }

    EyerIDR::EyerIDR(EyerNALU & _nalu, EyerSPS & _sps, EyerPPS & _pps) : EyerSLICEBase(_nalu, _sps, _pps)
    {

    }

    EyerIDR::~EyerIDR()
    {

    }
}