#include "EyerSlice.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    NaluType EyerSlice::GetNalType()
    {
        return NaluType::NALU_TYPE_SLICE;
    }

    EyerSlice::EyerSlice(EyerNALU & _nalu)
    {
        nalu = _nalu;

        nalu.ToSODB();
    }

    EyerSlice::~EyerSlice()
    {

    }
}