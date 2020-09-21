#include "EyerSPS.hpp"
#include "EyerBitStream.hpp"
#include "EyerAVC_VLC.hpp"
#include "EyerCore/EyerLog.hpp"

namespace Eyer{
    EyerSPS::EyerSPS(EyerNALU & _nalu)
    {
        nalu = _nalu;

        nalu.ToSODB();

        EyerBitStream bitStream(nalu.buf + 1, nalu.len - 1);
        bitStream.code_len = nalu.len - 1;
        bitStream.bitstream_length = nalu.len - 1;
        bitStream.ei_flag = 0;
        bitStream.read_len = 0;
        bitStream.frame_bitoffset = 0;

        int usedBits = 0;
        profile_idc = EyerAVC_VLC::read_u_v(8, "SPS: profile_idc", &bitStream, &usedBits);

        if ((profile_idc != BASELINE       ) &&
            (profile_idc != MAIN           ) &&
            (profile_idc != EXTENDED       ) &&
            (profile_idc != FREXT_HP       ) &&
            (profile_idc != FREXT_Hi10P    ) &&
            (profile_idc != FREXT_Hi422    ) &&
            (profile_idc != FREXT_Hi444    ) &&
            (profile_idc != FREXT_CAVLC444 ))
        {
            EyerLog("Invalid Profile IDC (%d) encountered. \n", profile_idc);
            return;
        }

        int reserved_zero;


        constrained_set0_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set0_flag"                 , &bitStream, &usedBits);
        constrained_set1_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set1_flag"                 , &bitStream, &usedBits);
        constrained_set2_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set2_flag"                 , &bitStream, &usedBits);
        constrained_set3_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set3_flag"                 , &bitStream, &usedBits);
        constrained_set4_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set4_flag"                 , &bitStream, &usedBits);
        constrained_set5_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set5_flag"                 , &bitStream, &usedBits);

        reserved_zero                          = EyerAVC_VLC::read_u_v  (2, "SPS: reserved_zero_2bits"          , &bitStream, &usedBits);

    }

    EyerSPS::~EyerSPS()
    {

    }

    int EyerSPS::PrintInfo()
    {
        EyerLog("profile_idc: %d\n", profile_idc);

        EyerLog("constrained_set0_flag: %d\n", constrained_set0_flag);
        EyerLog("constrained_set1_flag: %d\n", constrained_set1_flag);
        EyerLog("constrained_set2_flag: %d\n", constrained_set2_flag);
        EyerLog("constrained_set3_flag: %d\n", constrained_set3_flag);
        EyerLog("constrained_set4_flag: %d\n", constrained_set4_flag);
        EyerLog("constrained_set5_flag: %d\n", constrained_set5_flag);
        
        return 0;
    }
}
