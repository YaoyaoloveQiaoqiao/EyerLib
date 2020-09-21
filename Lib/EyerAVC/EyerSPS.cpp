#include "EyerSPS.hpp"

namespace Eyer{
    EyerSPS::EyerSPS(EyerNALU & _nalu)
    {
        nalu = _nalu;
        // profile_idc = read_u_v(8, "SPS: profile_idc", s, &p_Dec->UsedBits);
    }

    EyerSPS::~EyerSPS()
    {

    }

    int EyerSPS::PrintInfo()
    {
        return 0;
    }
}
