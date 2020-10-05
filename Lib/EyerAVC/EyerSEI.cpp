#include "EyerSEI.hpp"

namespace Eyer
{
    NaluType EyerSEI::GetNalType()
    {
        return NaluType::NALU_TYPE_SEI;
    }

    EyerSEI::EyerSEI(EyerNALU & _nalu)
    {
        nalu = _nalu;
    }

    EyerSEI::~EyerSEI()
    {

    }
}