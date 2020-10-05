#include "EyerIDR.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    NaluType EyerIDR::GetNalType()
    {
        return NaluType::NALU_TYPE_IDR;
    }

    EyerIDR::EyerIDR(EyerNALU & _nalu) : EyerSLICEBase(_nalu)
    {

    }

    EyerIDR::~EyerIDR()
    {

    }
}