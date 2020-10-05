#include "EyerIDR.hpp"

namespace Eyer
{
    NaluType EyerIDR::GetNalType()
    {
        return NaluType::NALU_TYPE_IDR;
    }

    EyerIDR::EyerIDR(EyerNALU & _nalu)
    {
        nalu = _nalu;
    }

    EyerIDR::~EyerIDR()
    {

    }
}